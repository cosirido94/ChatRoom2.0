#include "../include/broadcastUserDisconnectedMessageHandler.h"
#include "../client/include/client.h"
#include <QDebug>

void BroadCastUserDisconnectedMessageHandler::handleMessage(const QString &message)
{
    Client* clientInstance = Client::getInstance();
    if(!clientInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Client";
        return;
    }

    BroadCastUserDisconnectedMessage broadcastUserDisconnectedMsg = BroadCastUserDisconnectedMessage::deserialize(message);

    qDebug() << "Ricevuto messaggio di broadcast USER_CONNECTED"  << broadcastUserDisconnectedMsg.getUserName() << " " << broadcastUserDisconnectedMsg.getColorUserName();

    ChatRoom * chatRoomInstance = clientInstance->getChatRoom();
    if ( chatRoomInstance )
    {
        MessageWidget *message = new MessageWidget(broadcastUserDisconnectedMsg);
        chatRoomInstance->appendMessage(message);

        QString nicknameRemoved = broadcastUserDisconnectedMsg.getUserName();

        chatRoomInstance->getUserListWidget()->removeItem(nicknameRemoved);
        chatRoomInstance->updateNumberClientConnected();
    }
}