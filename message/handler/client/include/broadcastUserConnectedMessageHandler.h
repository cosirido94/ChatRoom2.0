#ifndef CHATROOM_BROADCASTUSERCONNECTEDMESSAGEHANDLER_H
#define CHATROOM_BROADCASTUSERCONNECTEDMESSAGEHANDLER_H

#include "clientMessageHandler.h"
#include "../../../type/include/broadcastUserConnectedMessage.h"
#include "../../../../chatroom/include/chatroom.h"
#include <QObject>
#include <QTcpSocket>

class BroadcastUserConnectedMessageHandler : public QObject , public ClientMessageHandler
{
    Q_OBJECT

public:
    BroadcastUserConnectedMessageHandler() = default;
    virtual void handleMessage( const QString& message );
};
#endif //CHATROOM_BROADCASTUSERCONNECTEDMESSAGEHANDLER_H
