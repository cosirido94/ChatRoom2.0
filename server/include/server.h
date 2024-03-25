#ifndef CHATROOM_MYSERVER_H
#define CHATROOM_MYSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QColor>

class Server : public QObject
{
    Q_OBJECT

public:
    Server(const QString &ipAddress , quint16 port );

};
#endif //CHATROOM_MYSERVER_H
