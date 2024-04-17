#ifndef CHATROOM_CHATROOMTEXTMESSAGEHANDLER_H
#define CHATROOM_CHATROOMTEXTMESSAGEHANDLER_H

#include "../include/serverMessageHandler.h"

class ChatRooomTextMessageHandler : public ServerMessageHandler
{

public:
    ChatRooomTextMessageHandler() = default;
    virtual void handleMessage(const QString& , QTcpSocket *client);
};
#endif //CHATROOM_CHATROOMTEXTMESSAGEHANDLER_H
