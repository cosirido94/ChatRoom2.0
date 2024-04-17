#ifndef CHATROOM_BROADCASTUSERDISCONNECTEDMESSAGEHANDLER_H
#define CHATROOM_BROADCASTUSERDISCONNECTEDMESSAGEHANDLER_H

#include "clientMessageHandler.h"
#include "../../../type/include/broadcastUserDisconnectedMessage.h"
#include "../../../chatroom/include/chatroom.h"
#include <QObject>

class BroadCastUserDisconnectedMessageHandler : public QObject , public ClientMessageHandler
{
    Q_OBJECT

public:
    BroadCastUserDisconnectedMessageHandler() = default;
    virtual void handleMessage( const QString& message );
};
#endif //CHATROOM_BROADCASTUSERDISCONNECTEDMESSAGEHANDLER_H
