#include "../include/client.h"
#include <QDataStream>
#include "../message/include/messageHandler.h"

Client::Client(QString nickname, QObject *parent)
{
    socket = new QTcpSocket(this);
    this->nickname = nickname;

    connect(socket,&QTcpSocket::connected,this,&Client::onConnected);
    connect(socket , &QTcpSocket::errorOccurred , this , &Client::onConnectionError);

    receiverThread = new ReceiverThread(socket,this);
    connect(receiverThread , &ReceiverThread::nickNameNotAvaiable , this , &Client::onNickNameNotAvailable);

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

    QString messageToSend = MessageHandler::addHeader(nickname,1);

    sendToServer(socket,messageToSend);

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
