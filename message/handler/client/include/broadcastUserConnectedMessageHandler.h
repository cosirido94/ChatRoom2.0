#ifndef CHATROOM_BROADCASTUSERCONNECTEDMESSAGEHANDLER_H
#define CHATROOM_BROADCASTUSERCONNECTEDMESSAGEHANDLER_H

#include "../include/clientMessageHandler.h"
#include "../../../type/include/broadcastUserConnectedMessage.h"
#include "../chatroom/include/chatroom.h"
#include <QObject>

class BroadcastUserConnectedMessageHandler : public QObject , public ClientMessageHandler
{
    Q_OBJECT

public:
    BroadcastUserConnectedMessageHandler() = default;
    virtual void handleMessage( const QString& message );
};
#endif //CHATROOM_BROADCASTUSERCONNECTEDMESSAGEHANDLER_H
