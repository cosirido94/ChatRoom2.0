#ifndef CHATROOM_MESSAGEWIDGET_H
#define CHATROOM_MESSAGEWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include "../message/type/include/broadcastUserConnectedMessage.h"
#include "../message/type/include/broadcastUserDisconnectedMessage.h"
#include "../message/type/include/chatroomTextMessage.h"

class MessageWidget : public QFrame
{
    Q_OBJECT

public:
    explicit MessageWidget(const BroadcastUserConnectedMessage& message , QWidget* parent = nullptr );
    explicit MessageWidget(const BroadCastUserDisconnectedMessage& message , QWidget* parent = nullptr );
    explicit MessageWidget(const ChatRoomTextMessage& message , QWidget* parent = nullptr);

private:
    void setupUi();
    QLabel *senderLabel;
    QLabel *textLabel;
    QLabel *timestampLabel;

};
#endif //CHATROOM_MESSAGEWIDGET_H
