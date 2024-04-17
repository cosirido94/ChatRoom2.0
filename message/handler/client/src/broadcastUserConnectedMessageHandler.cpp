#include "../include/broadcastUserConnectedMessageHandler.h"
#include "../client/include/client.h"
#include <QDebug>

void BroadcastUserConnectedMessageHandler::handleMessage(const QString& message)
{
    Client* clientInstance = Client::getInstance();
    if(!clientInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Client";
        return;
    }

    BroadcastUserConnectedMessage broadcastUserConnectedMsg = BroadcastUserConnectedMessage::deserialize(message);

    qDebug() << "Ricevuto messaggio di broadcast USER_CONNECTED"  << broadcastUserConnectedMsg.getUserName() << " " << broadcastUserConnectedMsg.getColorUserName();

    ChatRoom * chatRoomInstance = clientInstance->getChatRoom();
    if ( chatRoomInstance )
    {
        MessageWidget *message = new MessageWidget(broadcastUserConnectedMsg);
        chatRoomInstance->appendMessage(message);

        QString nicknameAdded = broadcastUserConnectedMsg.getUserName();
        QColor colorNicknameAdded = broadcastUserConnectedMsg.getColorUserName();

        /* Controllo necessario perchè sennò sul client stesso aggiunge 2 volte il Nome nella lista! */

        if (clientInstance->getNickName() != nicknameAdded )
        {
            chatRoomInstance->getUserListWidget()->addItem(nicknameAdded,colorNicknameAdded.name());
        }
        chatRoomInstance->updateNumberClientConnected();
    }
}