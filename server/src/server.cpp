#include "../include/server.h"
#include "../../message/type/include/broadcastUserDisconnectedMessage.h"
#include "../../message/handler/server/include/newUserMessageHandler.h"
#include "../../message/handler/server/include/chatroomReadyMessageHandler.h"
#include "../../message/handler/server/include/chatroomTextMessageHandler.h"
#include "../../message/parser/include/messageParser.h"
#include <QDataStream>
#include <QRandomGenerator>

Server* Server::instance = nullptr;

Server::Server(const QString &ipAddress, const quint16 port)
{
    configureServer(ipAddress , port);
    instance = this;
}

void Server::configureServer( const QString &ipAddress, const quint16 port )
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer , &QTcpServer::newConnection , this ,  &Server::handleNewConnection );

    QHostAddress address(ipAddress);

    if (tcpServer->listen(address,port))
    {
        qDebug() << "Server listening on" << address << ":" << port;
    }
    else
    {
        qDebug() << "Failed to start server" << tcpServer->errorString();
    }
//    nClientConnected = 0;
    setUserColors();
    serverMessageHandlers["NEW_USER"] = std::make_shared<NewUserMessageHandler>();
    serverMessageHandlers["CHATROOM_READY"] = std::make_shared<ChatRoomReadyMessageHandler>();
    serverMessageHandlers["CHATROOM_MESSAGE"] = std::make_shared<ChatRooomTextMessageHandler>();
}

void Server::setUserColors()
{
    userColors << QColor(255, 0, 0)  // Rosso scuro
               << QColor(0, 255, 0)  // Verde scuro
               << QColor(0, 0, 255)  // Blu scuro
               << QColor(255, 255, 0)  // Giallo scuro
               << QColor(0, 255, 255)  // Ciano scuro
               << QColor(255, 0, 255)  // Magenta scuro
               << QColor(128, 0, 0)  // Marrone scuro
               << QColor(0, 128, 0)  // Verde oliva scuro
               << QColor(0, 0, 128)  // Blu notte scuro
               << QColor(128, 128, 0)  // Verde oliva scuro
               << QColor(128, 0, 128)  // Viola scuro
               << QColor(0, 128, 128)  // Verde acqua scuro
               << QColor(128, 128, 128)  // Grigio scuro
               << QColor(64, 0, 0)  // Rosso scuro
               << QColor(0, 64, 0)  // Verde scuro
               << QColor(0, 0, 64)  // Blu scuro
               << QColor(64, 64, 0)  // Giallo scuro
               << QColor(0, 64, 64)  // Ciano scuro
               << QColor(64, 0, 64);  // Magenta scuro
}

void Server::handleNewConnection()
{
    qDebug() << "Nuovo client connesso!";
    QTcpSocket* clientSocket = tcpServer->nextPendingConnection();

    if (clientSocket)
    {
        connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
            readClientData(clientSocket);
        });
        connect( clientSocket , &QTcpSocket::disconnected , this , &Server::disconnectClient);
    }
}

void Server::readClientData(QTcpSocket *client)
{
    if (client->bytesAvailable() > 0)
    {

        QDataStream in(client);
        in.setVersion(QDataStream::Qt_5_15);

        QString message;
        in >> message;

        qDebug() << "Server riceve messaggio : " << message;

        QString header = MessageParser::extractHeader(message);
//        QString body = MessageParser::extractBody(message);
        handleMessage(header, message, client);
    }
}

void Server::handleMessage(const QString header , const QString message , QTcpSocket* client )
{
    auto it = serverMessageHandlers.find(header);
    if (it != serverMessageHandlers.end())
    {
        it.value()->handleMessage(message,client);
    }
    else
    {
        // Gestisci caso in cui l'header non è riconosciuto
    }
}

void Server::disconnectClient()
{
    QTcpSocket* disconnectedClient = qobject_cast<QTcpSocket*>(sender());

    if (disconnectedClient && usersMap.contains(disconnectedClient) )
    {
        User userInfo = usersMap.value(disconnectedClient);

        QColor clientColor = userInfo.getColor();
        QString userName = userInfo.getNickName();
        userColors.append(clientColor);

        usersMap.remove(disconnectedClient);
        /*** Dovrà essere mandato un messaggio di broadcast a tutti i client connessi ***/

        disconnectedClient->deleteLater();

        qDebug() << "Client " << userName << " disconnected";

        QString broadCastUserDisconnectedMsg = BroadCastUserDisconnectedMessage(userName,clientColor).serialize();
        sendBroadCastMessage(broadCastUserDisconnectedMsg);
    }
}

void Server::registerNewUser(QTcpSocket* client ,QString nickname)
{
    QColor clientColor =  assignColorToClient();
    User user(nickname,clientColor);
    usersMap.insert(client,user);

    qDebug() << "Nuovo client registrato";
    printUsersList();
}

Server::~Server()
{
    closeAllConnection();

    if (tcpServer && tcpServer->isListening() )
    {
        tcpServer->close();
        delete tcpServer;
        tcpServer = nullptr;
    }

    // Pulisci la mappa degli utenti

    usersMap.clear();
    userColors.clear();
}

void Server::closeAllConnection()
{
    QMap<QTcpSocket*,User>::iterator it = usersMap.begin();
    while( it!= usersMap.end() )
    {
        QTcpSocket *socket = it.key();
        socket->close();
        socket->deleteLater();
        it = usersMap.erase(it);
    }
}

void Server::sendToClient(QTcpSocket *socket, const QString &message)
{
    // Crea un array di byte per memorizzare i dati serializzati
    QByteArray byteArray;

    // Crea un flusso di dati e collegalo all'array di byte
    QDataStream dataStream(&byteArray,QIODevice::WriteOnly);

    // Scrivi la stringa nel flusso di dati
    dataStream << message;

    // Scrivi l'array di byte sulla socket
    socket->write(byteArray);

    // Flusso dei dati per assicurarsi che i dati siano inviati immediatamente
    socket->flush();
}

QColor Server::generateRandomColor()
{
    if (!userColors.isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(userColors.size());
        return userColors[randomIndex];
    }

    return Qt::black;
}

QColor Server::assignColorToClient()
{
    QColor clientColor = generateRandomColor();

    userColors.removeAll(clientColor);

    return clientColor;
}

/**** Da testare ****/

bool Server::isNickNameAvaialable(QTcpSocket* client,const QString &nickname)
{
    QMap<QTcpSocket*,User>::const_iterator i = usersMap.constBegin();

    while (i != usersMap.constEnd() )
    {
        User userInfo = i.value();

        if(userInfo.getNickName() == nickname )
        {
            return false;
        }
        ++i;
    }
    return true;
}

void Server::printUsersList()
{
    QMap<QTcpSocket*, User>::const_iterator it;
    for (it = usersMap.constBegin(); it != usersMap.constEnd(); ++it)
    {
        qDebug() << "Socket:" << it.key() << "Nickname:" << it.value().getNickName() << "Color:" << it.value().getColor();
    }
}

Server* Server::getInstance()
{
    if(!instance)
    {
        qDebug() << "Errore: Nessuna istanza del server è stata creata!";
        return nullptr;
    }
    return instance;
}
QMap<QTcpSocket*,User> Server::getUsersMap()
{
    return usersMap;
}

void Server::sendBroadCastMessage(const QString &message)
{
    for ( QTcpSocket* receiver : usersMap.keys() )
    {
        sendToClient(receiver,message);
        qDebug() << "Invio broadcast a " << usersMap.value(receiver).getNickName();
    }
}


/**** ****/