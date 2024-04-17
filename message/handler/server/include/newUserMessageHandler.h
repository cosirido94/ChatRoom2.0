#ifndef CHATROOM_NEWUSERMESSAGEHANDLER_H
#define CHATROOM_NEWUSERMESSAGEHANDLER_H

#include "../include/serverMessageHandler.h"

class NewUserMessageHandler : public ServerMessageHandler
{
public:
    NewUserMessageHandler() = default;
    virtual void handleMessage(const QString& message , QTcpSocket *client);
};

#endif //CHATROOM_NEWUSERMESSAGEHANDLER_H
