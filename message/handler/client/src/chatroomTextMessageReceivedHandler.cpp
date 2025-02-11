#include "../include/chatroomTextMessageReceivedHandler.h"
#include "../client/include/client.h"
#include <QDebug>

void ChatRoomTextMessageReceivedHandler::handleMessage(const QString &message)
{
    Client* clientInstance = Client::getInstance();
    if(!clientInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Client";
        return;
    }

    ChatRoomTextMessage chatroomTextMsg = ChatRoomTextMessage::deserialize(message);
    qDebug() << "Ricevuto messaggio di chatroom CHATROOM " << chatroomTextMsg.getSender() << " text: " << chatroomTextMsg.getText();

    ChatRoom *chatRoomInstance = clientInstance->getChatRoom();
    if(chatRoomInstance)
    {
//        MessageWidget *message = new MessageWidget( chatroomTextMsg);
//        chatRoomInstance->appendMessage(message);
        chatRoomInstance->appendNewMessage(chatroomTextMsg);
    }
}