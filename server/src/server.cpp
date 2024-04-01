#include "../include/server.h"
#include "../message/include/messageHandler.h"
#include <QDataStream>
#include <QRandomGenerator>

Server::Server(const QString &ipAddress, const quint16 port)
{
    configureServer(ipAddress , port);
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
    }
}

void Server::readClientData(QTcpSocket *client)
{
    if (client->bytesAvailable() > 0)
    {
        // Crea un flusso di dati e collegalo alla socket

        QDataStream in(client);
        in.setVersion(QDataStream::Qt_5_15);

        QString message;
        in >> message;

        QString header = MessageHandler::extractHeader(message);

        if( header != QString() )
        {
            QString messageBody = MessageHandler::extractMessage(message);
            handleMessage(header , messageBody , client);
        }
    }
}

void Server::handleMessage(const QString header , const QString message , QTcpSocket* client )
{
    if ( header == "NEW_USER" )
    {
        if ( isNickNameAvaialable(client,message) )
        {
            registerNewUser(client,message);

            QColor clientColor = usersMap.value(client).getColor();
            QString colorString = clientColor.name();
            QString messageColor = MessageHandler::addHeader(colorString,2);
            sendToClient(client,messageColor);
            qDebug() << "Invio del colore ";
        }
        else
        {
            QString messageError = MessageHandler::addHeader("",3);
            sendToClient(client,messageError);
            qDebug() << "Invio messaggio di errore nickname non disponibile";
        }
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
    for (it = usersMap.constBegin(); it != usersMap.constEnd(); ++it) {
        qDebug() << "Socket:" << it.key() << "Nickname:" << it.value().getNickName() << "Color:" << it.value().getColor();
    }
}



/**** ****/