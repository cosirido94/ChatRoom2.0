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

    qDebug() << "Ricevuto messaggio di broadcast USER_DISCONNECTED"  << broadcastUserDisconnectedMsg.getUserName() << " " << broadcastUserDisconnectedMsg.getColorUserName();

    ChatRoom * chatRoomInstance = clientInstance->getChatRoom();
    if ( chatRoomInstance )
    {
//        MessageWidget *message = new MessageWidget(broadcastUserDisconnectedMsg);
//        chatRoomInstance->appendMessage(message);

        QString nicknameRemoved = broadcastUserDisconnectedMsg.getUserName();

//        chatRoomInstance->getUserListWidget()->removeItem(nicknameRemoved);
        chatRoomInstance->updateUserList(nicknameRemoved,QColor(),false);
        chatRoomInstance->updateNumberClientConnected();
        chatRoomInstance->updateChatItemStatus(nicknameRemoved,false); // Metti lo status Offline se chatItem aperto
    }
}