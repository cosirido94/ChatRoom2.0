#ifndef CHATROOM_PRIVATECHATITEM_H
#define CHATROOM_PRIVATECHATITEM_H

#include "chatItem.h"

class PrivateChatItem : public ChatItem
{
    Q_OBJECT

public:
    explicit PrivateChatItem(const QString &username , QWidget *parent = nullptr);
    void setOnlineStatus(bool isOnline);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QPushButton *closeButton;
    QLabel *statusOnline;

signals:
    void closeRequested(PrivateChatItem *item);

private slots:
    void onCloseButtonClicked();
};
#endif //CHATROOM_PRIVATECHATITEM_H
