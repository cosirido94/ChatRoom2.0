#include <QDataStream>
#include "../include/client.h"
#include "../../message/handler/client/include/clientMessageHandler.h"
#include "../../message/type/include/newUserMessage.h"
#include "../../message/type/include/chatroomReadyMessage.h"
#include "../../message/type/include/chatroomTextMessage.h"
#include "../../message/handler/client/include/errorNickMessageHandler.h"
#include "../../message/handler/client/include/configChatMessageHandler.h"
#include "../../message/handler/client/include/broadcastUserConnectedMessageHandler.h"
#include "../../message/handler/client/include/broadcastUserDisconnectedMessageHandler.h"
#include "../../message/handler/client/include/chatroomTextMessageReceivedHandler.h"


Client * Client::instance = nullptr;

Client::Client(QString nickname, QObject *parent)
{
    socket = new QTcpSocket(this);
    this->nickname = nickname;

    connect(socket,&QTcpSocket::connected,this,&Client::onConnected);
    connect(socket , &QTcpSocket::errorOccurred , this , &Client::onConnectionError);

    clientMessageHandlers["ERROR_NICK"] = std::make_shared<ErrorNickMessageHandler>();
    clientMessageHandlers["CONFIG_CHAT"] = std::make_shared<ConfigChatMessageHandler>();
    clientMessageHandlers["BROADCAST_USER_CONNECTED"] = std::make_shared<BroadcastUserConnectedMessageHandler>();
    clientMessageHandlers["BROADCAST_USER_DISCONNECTED"] = std::make_shared<BroadCastUserDisconnectedMessageHandler>();
    clientMessageHandlers["CHATROOM_MESSAGE"] = std::make_shared<ChatRoomTextMessageReceivedHandler>();

    receiverThread = new ReceiverThread(socket,this);
//    connect(receiverThread , &ReceiverThread::nickNameNotAvaiable , this , &Client::onNickNameNotAvailable);
    connect(receiverThread , &ReceiverThread::messageReceived , this , &Client::handleMessage);
    auto errorNickHandler = std::dynamic_pointer_cast<ErrorNickMessageHandler>(clientMessageHandlers["ERROR_NICK"]);
    auto configChatHandler = std::dynamic_pointer_cast<ConfigChatMessageHandler>(clientMessageHandlers["CONFIG_CHAT"]);
    connect(errorNickHandler.get(), &ErrorNickMessageHandler::notifyClient , this ,&Client::onNickNameNotAvailable );
    connect(configChatHandler.get(), &ConfigChatMessageHandler::notifyCloseClientDialog , this , &Client::closeClientDialog );
    instance = this;
    chatRoom = nullptr;
//    receiverThread = new ReceiverThread(socket);
//    receiverThread->start();
//    receiverThread = new ReceiverThread(socket,this);
//    connect(receiverThread , &ReceiverThread::nickNameNotAvaiable , this , &Client::onNickNameNotAvailable);
//    receiverThread->start();


}

void Client::connectToServer(const QString &ipAddress, quint16 port)
{
    socket->connectToHost("127.0.0.1" , 8081 );
}

void Client::onConnected()
{
    qDebug() << "Connected to server!";

//    receiverThread = new ReceiverThread(socket,this);
//    connect(receiverThread , &ReceiverThread::nickNameNotAvaiable , this , &Client::onNickNameNotAvailable);
    receiverThread->start();

//    QString messageToSend = MessageHandler::addHeader(nickname,1);
    QString newUserMsg = NewUserMessage(nickname).serialize();
    qDebug () << "Messaggio inviato "<< newUserMsg;

//    sendToServer(socket,messageToSend);
    sendToServer(socket,newUserMsg);

    emit connectionEstablished();
}

void Client::sendToServer(QTcpSocket *socket, const QString &message)
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


void Client::onConnectionError( QAbstractSocket::SocketError error )
{
    qDebug() << "Connection error " << error;
    emit connectionError();
}

void Client::onNickNameNotAvailable()
{
    emit showMessageClientNotAvailable();
}

Client::~Client()
{
    /* Sconnetti i segnali associati a myClient in client */

    disconnect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    disconnect(socket, &QTcpSocket::errorOccurred, this, &Client::onConnectionError);

    /* Setting della socket (di myClient) a nullptr ma verrà distrutta nel distruttore di ReceiverThread */

    socket = nullptr;
    clearReceiverThread();
}

void Client::clearReceiverThread()
{
    if (receiverThread)
    {
        /* Scollega il segnale associato a MyClient */

        disconnect(receiverThread, &ReceiverThread::nickNameNotAvaiable, this, &Client::onNickNameNotAvailable);

        /* Chiama il distruttore di ReceiverThread */

        delete receiverThread;
        receiverThread = nullptr;
    }
}

ReceiverThread* Client::getReceiverThread()
{
    return receiverThread;
}

QTcpSocket* Client::getSocket()
{
    return socket;
}

void Client::handleMessage(const QString header, const QString message)
{
    auto it = clientMessageHandlers.find(header);
    if( it != clientMessageHandlers.end() )
    {
        it.value()->handleMessage(message);
    }
    else
    {
        // Gestisci caso in cui l'header non è riconosciuto
    }
}

Client* Client::getInstance()
{
    if(!instance)
    {
        qDebug() << "Errore: Nessuna istanza del Client è stata creata!";
        return nullptr;
    }
    return instance;
}
ChatRoom* Client::getChatRoom()
{
    return chatRoom;
}

QString Client::getNickName()
{
    return nickname;
}

void Client::setChatRoom(ChatRoom *chatroom)
{
    this->chatRoom = chatroom;
}


void Client::closeClientDialog()
{
    emit shutClientDialog();
    openChatRoom();
}

void Client::openChatRoom()
{
    connect(chatRoom , &ChatRoom::chatRoomReady , this , &Client::sendChatRoomReady);
    connect(chatRoom , &ChatRoom::messageSent , this , &Client::sendChatRoomMessage);

    chatRoom->configureChatRoom();
    chatRoom->show();
}

void Client::sendChatRoomReady( QColor userColor )
{
    QString chatRoomReadyMsg = ChatRoomReadyMessage(nickname,userColor).serialize();
    sendToServer(socket,chatRoomReadyMsg);
    qDebug () << "Messaggio ChatRoom READY "<< chatRoomReadyMsg;
}

void Client::sendChatRoomMessage(const QColor userColor,const QString message)
{
    QString chatroomTextMsg = ChatRoomTextMessage(nickname,userColor,message).serialize();
    sendToServer(socket,chatroomTextMsg);
    qDebug() << "Messaggio di testo inviato ";
}