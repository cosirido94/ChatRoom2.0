#include "../include/newUserMessageHandler.h"
#include "../include/newUserMessage.h"
#include "../include/errorNickMessage.h"
#include "../server/include/server.h"

void NewUserMessageHandler::handleMessage(const QString& message, QTcpSocket *client)
{
    Server* serverInstance = Server::getInstance();
    if(!serverInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Server";
        return;
    }

    NewUserMessage newUserMsg(message);
    QString nickname = newUserMsg.getNickName();
    qDebug() << "Messaggio ricevuto dal client " << message;
    qDebug() << "Nickname: " << nickname;

    if(serverInstance->isNickNameAvaialable(client,nickname) )
    {
        serverInstance->registerNewUser(client,nickname);
        qDebug() << "Utente registrato";
    }
    else
    {
        QString errorNickMsg = ErrorNickMessage().serialize();
        qDebug() << "Invio messaggio di errore " << errorNickMsg;
        serverInstance->sendToClient(client,errorNickMsg);
    }

}
