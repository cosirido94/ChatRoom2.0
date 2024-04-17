#ifndef CHATROOM_CHATROOMREADYMESSAGEHANDLER_H
#define CHATROOM_CHATROOMREADYMESSAGEHANDLER_H

#include "../include/serverMessageHandler.h"

class ChatRoomReadyMessageHandler : public ServerMessageHandler
{

public:
    ChatRoomReadyMessageHandler() = default;
    virtual void handleMessage(const QString& message , QTcpSocket *client);
    void sendBroadcastUserConnectedMessage( const QString& message);
};

#endif //CHATROOM_CHATROOMREADYMESSAGEHANDLER_H
