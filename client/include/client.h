#ifndef CHATROOM_CLIENT_H
#define CHATROOM_CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include "../thread/include/receiverThread.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QString nickname , QObject* parent = nullptr );
    ReceiverThread* getReceiverThread() ;
    QTcpSocket* getSocket();
    ~Client();
    void connectToServer(const QString& ipAddress , quint16 port );
private slots:
    void onConnected();
    void onConnectionError( QAbstractSocket::SocketError error );
    void onNickNameNotAvailable();
private:
    QTcpSocket* socket;
    QString nickname;
    ReceiverThread *receiverThread;

private:
    void sendToServer(QTcpSocket *socket , const QString& message);
    void clearReceiverThread();

signals:
    void connectionEstablished();
    void connectionError();
    void showMessageClientNotAvailable();
};
#endif //CHATROOM_CLIENT_H
