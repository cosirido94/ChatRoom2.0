#ifndef CHATROOM_MYSERVER_H
#define CHATROOM_MYSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QColor>
#include "../include/user.h"
#include "../../message/handler/server/include/serverMessageHandler.h"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(const QString &ipAddress , const quint16 port );
    ~Server();
    static Server* getInstance();
    bool isNickNameAvaialable(QTcpSocket* client ,const QString& nickname);
    void registerNewUser( QTcpSocket* client , QString nickname );
    QColor assignColorToClient();
    void sendToClient(QTcpSocket *socket , const QString& message);
    void sendBroadCastMessage(const QString& message );

    QMap<QTcpSocket*,User> getUsersMap();
private:
    QTcpServer *tcpServer;
    QList <QColor> userColors;
    QMap <QTcpSocket*,User> usersMap;
    QMap <QString , std::shared_ptr<ServerMessageHandler>> serverMessageHandlers;

    static Server* instance;
private:
    void configureServer( const QString &ipAddress, const quint16 port );
    void setUserColors();
    QColor generateRandomColor();
    void handleMessage( const QString header , const QString message , QTcpSocket* client);
    void printUsersList();
    void closeAllConnection();


private slots:
    void handleNewConnection();
    void readClientData( QTcpSocket *socket );
    void disconnectClient();

};
#endif //CHATROOM_MYSERVER_H
