#ifndef CHATROOM_NEWUSERMESSAGEHANDLER_H
#define CHATROOM_NEWUSERMESSAGEHANDLER_H

#include "../include/messageHandler.h"

class NewUserMessageHandler : public MessageHandler
{
public:
    NewUserMessageHandler() = default;
    virtual void handleMessage(const QString& message , QTcpSocket *client);
};

#endif //CHATROOM_NEWUSERMESSAGEHANDLER_H
