#ifndef CHATROOM_MESSAGEHANDLER_H
#define CHATROOM_MESSAGEHANDLER_H

//#include <QString>
//#include <QMap>
//
//class MessageHandler
//{
//public:
//    static QString addHeader(const QString message , int opcode);
//    static QString extractHeader(const QString& message);
//    static QString extractMessage(const QString message );
//    static QMap<int,QString> headers;
//};
#include <QString>
#include <QTcpSocket>

class MessageHandler
{
public:
    virtual void handleMessage(const QString& message, QTcpSocket* client) = 0;
    virtual ~MessageHandler() {}
};

#endif //CHATROOM_MESSAGEHANDLER_H
