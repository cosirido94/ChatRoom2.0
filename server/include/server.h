#ifndef CHATROOM_MYSERVER_H
#define CHATROOM_MYSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QColor>
#include "../include/user.h"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(const QString &ipAddress , const quint16 port );
    ~Server();
private:
    QTcpServer *tcpServer;
    QList <QColor> userColors;
    QMap <QTcpSocket*,User> usersMap;
private:
    void configureServer( const QString &ipAddress, const quint16 port );
    void setUserColors();
    QColor generateRandomColor();
    QColor assignColorToClient();
    bool isNickNameAvaialable(QTcpSocket* client ,const QString& nickname);
    void handleMessage( const QString header , const QString message , QTcpSocket* client);
    void registerNewUser( QTcpSocket* client , QString nickname );
    void sendToClient(QTcpSocket *socket , const QString& message);
    void printUsersList();
    void closeAllConnection();
private slots:
    void handleNewConnection();
    void readClientData( QTcpSocket *socket );

};
#endif //CHATROOM_MYSERVER_H
