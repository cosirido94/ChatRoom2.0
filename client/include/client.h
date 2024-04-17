#ifndef CHATROOM_CLIENT_H
#define CHATROOM_CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include "../thread/include/receiverThread.h"
#include "../../message/handler/client/include/clientMessageHandler.h"
#include "../chatroom/include/chatroom.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QString nickname , QObject* parent = nullptr );
    ReceiverThread* getReceiverThread() ;
    QTcpSocket* getSocket();
    ~Client();
    static Client* getInstance();
    void connectToServer(const QString& ipAddress , quint16 port );
    ChatRoom* getChatRoom();
    QString getNickName();
    void setChatRoom( ChatRoom* );
private slots:
    void onConnected();
    void onConnectionError( QAbstractSocket::SocketError error );
    void onNickNameNotAvailable();
    void handleMessage(const QString header , const QString message);
    void closeClientDialog();
    void sendChatRoomReady( QColor userColor );
    void sendChatRoomMessage( const QColor, const QString message);
private:
    QTcpSocket* socket;
    QString nickname;
    ReceiverThread *receiverThread;
    QMap <QString , std::shared_ptr<ClientMessageHandler>> clientMessageHandlers;

    static Client* instance;
    ChatRoom* chatRoom;
private:
    void sendToServer(QTcpSocket *socket , const QString& message);
    void clearReceiverThread();
    void openChatRoom();

signals:
    void connectionEstablished();
    void connectionError();
    void showMessageClientNotAvailable();
    void shutClientDialog();
};
#endif //CHATROOM_CLIENT_H
