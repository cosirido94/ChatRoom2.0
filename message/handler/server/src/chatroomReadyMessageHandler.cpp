#include "../include/chatroomReadyMessageHandler.h"
#include "../../../type/include/chatroomReadyMessage.h"
#include "../../../type/include/broadcastUserConnectedMessage.h"
#include "../../../../server/include/server.h"

void ChatRoomReadyMessageHandler::handleMessage(const QString &message, QTcpSocket *client)
{
    Server* serverInstance = Server::getInstance();
    if(!serverInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Server";
        return;
    }

    BroadcastUserConnectedMessage broadcastUserConnectedMsg = BroadcastUserConnectedMessage::deserialize(message);

    QString userName = broadcastUserConnectedMsg.getUserName();
    QColor userColor = broadcastUserConnectedMsg.getColorUserName();

    QString broadCastMsg = BroadcastUserConnectedMessage(userName,userColor).serialize();

    sendBroadcastUserConnectedMessage(broadCastMsg);
}

void ChatRoomReadyMessageHandler::sendBroadcastUserConnectedMessage( const QString& message )
{
    Server* serverInstance = Server::getInstance();
    if(!serverInstance)
    {
        qDebug() << "Impossibile ottenere un'istanza del Server";
        return;
    }
    for( QTcpSocket* receiver : serverInstance->getUsersMap().keys() )
    {
        serverInstance->sendToClient(receiver,message);
        qDebug() << "Invio broadcast a " << serverInstance->getUsersMap().value(receiver).getNickName();
    }
}