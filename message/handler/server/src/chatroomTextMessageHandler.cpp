#include "../include/chatroomTextMessageHandler.h"
#include "../../../type/include/chatroomTextMessage.h"
#include "../../../../server/include/server.h"

void ChatRooomTextMessageHandler::handleMessage(const QString &message, QTcpSocket *client)
{
    Server* serverInstance = Server::getInstance();
    if(!serverInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Server";
        return;
    }
    qDebug() << "Messaggio di testo arrivato al Server : " << message;
    serverInstance->sendBroadCastMessage(message);
}