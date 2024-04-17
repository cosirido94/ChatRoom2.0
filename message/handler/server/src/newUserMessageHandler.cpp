#include "../include/newUserMessageHandler.h"
#include "../../../type/include/newUserMessage.h"
#include "../../../type/include/errorNickMessage.h"
#include "../../../type/include/configChatMessage.h"
#include "../../../../server/include/server.h"

void NewUserMessageHandler::handleMessage(const QString& message, QTcpSocket *client)
{
    Server* serverInstance = Server::getInstance();
    if(!serverInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Server";
        return;
    }

    NewUserMessage newUserMsg = NewUserMessage::deserialize(message);
    QString nickname = newUserMsg.getNickName();

    if(serverInstance->isNickNameAvaialable(client,nickname) )
    {
        serverInstance->registerNewUser(client,nickname);
        qDebug() << "Utente registrato";
        QMap<QTcpSocket*,User> usersMap = serverInstance->getUsersMap();
        QColor clientColor = usersMap.value(client).getColor();

        QList<User> userList;
        for(const User& user : usersMap)
        {
            userList.append(user);
        }
        QString configChatMessage = ConfigChatMessage(clientColor,userList).serialize();
        qDebug() << "Invio messaggio di config " + configChatMessage;
        serverInstance->sendToClient(client,configChatMessage);
    }
    else
    {
        QString errorNickMsg = ErrorNickMessage().serialize();
        qDebug() << "Invio messaggio di errore " << errorNickMsg;
        serverInstance->sendToClient(client,errorNickMsg);
    }
}
