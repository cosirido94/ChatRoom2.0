#ifndef CHATROOM_CHATROOMTEXTMESSAGERECEIVEDHANDLER_H
#define CHATROOM_CHATROOMTEXTMESSAGERECEIVEDHANDLER_H

#include "clientMessageHandler.h"
#include "../../../type/include/chatroomTextMessage.h"
#include "../../../chatroom/include/chatroom.h"
#include <QObject>

class ChatRoomTextMessageReceivedHandler : public QObject , public ClientMessageHandler
{
    Q_OBJECT

public:
    ChatRoomTextMessageReceivedHandler() = default;
    virtual void handleMessage(const QString& message );
};

#endif //CHATROOM_CHATROOMTEXTMESSAGERECEIVEDHANDLER_H
