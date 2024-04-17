#include "../include/configChatMessageHandler.h"
#include "../client/include/client.h"
#include <qdebug.h>

void ConfigChatMessageHandler::handleMessage(const QString &message)
{
    Client* clientInstance = Client::getInstance();
    if(!clientInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Client";
        return;
    }

    ConfigChatMessage configChatMsg = ConfigChatMessage::deserialize(message);
    QString nickname = clientInstance->getNickName();
    QColor userColor = configChatMsg.getColor();
    qDebug() << "Utenti connessi: ";
    QList<User> usersList = configChatMsg.getUserList();

    for(const User& user : usersList)
    {
        qDebug() << "Nickname: " << user.getNickName() << ", Colore: " <<user.getColor().name();
    }

    if( !clientInstance->getChatRoom() )
    {
        ChatRoom *chatRoom = createChatRoom( nickname , configChatMsg );
        clientInstance->setChatRoom(chatRoom);
        emit notifyCloseClientDialog();
    }
}

ChatRoom* ConfigChatMessageHandler::createChatRoom(const QString nickname ,const ConfigChatMessage &configChatMessage)
{
    QColor userColor = configChatMessage.getColor();
    QList<User> usersList = configChatMessage.getUserList();

    ChatRoom * chatRoom = new ChatRoom(nickname,userColor,usersList);

    qDebug() << "ChatRoom creata!";
    return chatRoom;
}

