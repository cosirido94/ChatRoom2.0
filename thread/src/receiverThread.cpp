#include "../include/receiverThread.h"
#include <QDataStream>
#include "../message/include/messageHandler.h"


ReceiverThread::ReceiverThread(QTcpSocket *socket, QObject *parent)
        : QThread(parent) , socket(socket)
{
    connect(socket,&QTcpSocket::readyRead , this , &ReceiverThread::readData);
}

void ReceiverThread::run()
{
    qDebug() << "Receiver Thread is running";
    exec();
}
void ReceiverThread::readData()
{
//     Verifica se il socket è ancora valido
    if (!socket )
    {
        return;
    }

    while (socket && socket->isValid() && socket->bytesAvailable() > 0  )
    {
        if (!socket)
        {
            return;
        }
        QByteArray data = socket->readAll();
        QDataStream in(&data, QIODevice::ReadOnly);

        QString message;
        in >> message;

        QString header = MessageHandler::extractHeader(message);

        if( header != QString() )
        {
            QString messageBody = MessageHandler::extractMessage(message);
            handleMessage(header,message);
        }
    }
}

QTcpSocket* ReceiverThread::getSocket() const
{
    return socket;
}

void ReceiverThread::handleMessage(const QString header, const QString message)
{
    if (header == "NICKNAME_NOT_AVAILABLE")
    {
        qDebug() << "Messaggio di errore ricevuto";
        stopThread();
        emit nickNameNotAvaiable();
    }
}

ReceiverThread::~ReceiverThread()
{
    stopThread();
    clearSocket();
}

void ReceiverThread::stopThread()
{
    if (this && this->isRunning())
    {
        this->quit();
        this->wait();
    }
}

void ReceiverThread::clearSocket()
{
    if (socket->isOpen())
    {
        socket->close();
    }
    if (socket)
    {
        /* Scollega la socket per ricevere messaggi */

        disconnect(socket,&QTcpSocket::readyRead , this , &ReceiverThread::readData);

        delete socket;
        socket = nullptr;
    }
}

