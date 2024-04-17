#ifndef CHATROOM_CHATROOM_H
#define CHATROOM_CHATROOM_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QListWidget>
#include <QTcpSocket>
#include <QColor>
#include "../server/include/user.h"
#include "../custom/include/sortedListWidget.h"
#include "../custom/include/clickLabel.h"
#include "../custom/include/messageWidget.h"

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(const QString nickname , const QColor userColor , const QList<User> usersList , QWidget *parent = nullptr );
    void configureChatRoom();
    static ChatRoom* getInstance();
    void appendMessage( MessageWidget* message);
    void updateNumberClientConnected();
    SortedListWidget* getUserListWidget() const;
private:
    QString nickname;
    QColor userColor;

    QList<User> usersList;
    static ChatRoom* instance;
    ClickLabel *chatRoomLabel;
    QLabel *messageLabel;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QVBoxLayout *chatDisplayLayout;  // Layout per i MessageWidget
    QScrollArea *scrollArea;  // Permette la visualizzazione di più messaggi
    QWidget *chatDisplayContainer;  // Contenitore per chatDisplayLayout
    QGridLayout *mainLayout;

    QLineEdit *userSearchInput;
    SortedListWidget *userListWidget;
    QLabel *connectedUsersLabel;
private:
    void fillUserListWidget();
    void updateScrollBar();

signals:
    void chatRoomReady( QColor userColor );
    void messageSent( const QColor colorSender , const QString message );

private slots:
    void onClickSendMessage();
};


#endif //CHATROOM_CHATROOM_H
