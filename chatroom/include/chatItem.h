#ifndef CHATROOM_CHATITEM_H
#define CHATROOM_CHATITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../custom/include/clickLabel.h"

class ChatItem : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItem(const QString &chatId , QWidget *parent = nullptr);
    virtual ~ChatItem() = default;
    QString getChatId();
    virtual void updateUnreadMessages(int count);

protected:
    QString chatId;
    QLabel *unreadMessageCountLabel;
    ClickLabel *userNameLabel;

};
#endif //CHATROOM_CHATITEM_H
