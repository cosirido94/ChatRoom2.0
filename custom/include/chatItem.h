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
    explicit ChatItem(QWidget *parent = nullptr);
    explicit ChatItem(const QString &username , QWidget *parent = nullptr);
    QString getUserName();
    void setOnlineStatus(bool isOnline);

private:
    QLabel *statusOnline{};
    ClickLabel *userNameLabel{};
    QPushButton *closeButton{};
    QLabel *unreadMessageCountLabel{};
    QString username;

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    void closeRequested(ChatItem *item);

private:
    void createWidgets();
    void createLayout();

private slots:
//    void handleClick();
    void onCloseButtonClicked();
};
#endif //CHATROOM_CHATITEM_H
