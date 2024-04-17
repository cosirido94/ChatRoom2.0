#ifndef CHATROOM_CLIENTMESSAGEHANDLER_H
#define CHATROOM_CLIENTMESSAGEHANDLER_H

#include <QString>
#include <QTcpSocket>
class ClientMessageHandler
{

public:
    virtual void handleMessage(const QString& message) = 0;
    virtual ~ClientMessageHandler(){}

};
#endif //CHATROOM_CLIENTMESSAGEHANDLER_H
