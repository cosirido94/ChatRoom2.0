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
#include <QStackedWidget>
#include <QTextEdit>

#include "../server/include/user.h"
#include "../custom/include/sortedListWidget.h"
#include "../custom/include/clickLabel.h"
#include "../custom/include/messageWidget.h"
#include "../include/privateChatItem.h"
#include "../include/publicChatItem.h"
//#include "../custom/include/chatItem.h"

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(const QString nickname , const QColor userColor , const QList<User> usersList , QWidget *parent = nullptr );
    void configureChatRoom();
    static ChatRoom* getInstance();
    void appendMessage( MessageWidget* message);
    SortedListWidget* getUserListWidget() const;
    void chatroomReadyNotify();
    void updateNumberClientConnected();
    void updateUserList(QString username , QColor colorUsername , bool op);
    void updateChatItemStatus(const QString &nickname , bool isOnline);
    void appendNewMessage(const Message& message);
    QString getNickname();

private:
    QString nickname;
    QColor userColor;
    QList<User> usersList;

    static ChatRoom* instance;
    ClickLabel *chatRoomLabel;
    QScrollArea *scrollUserWidgetArea;
    QWidget *userWidgetContainer;

    QLineEdit *messageInput;
    QPushButton *sendButton;
    QVBoxLayout *chatDisplayLayout;  // Layout per i MessageWidget
    QScrollArea *scrollArea;  // Permette la visualizzazione di più messaggi
    QWidget *chatDisplayContainer;  // Contenitore per chatDisplayLayout

    QLineEdit *userSearchInput;
    SortedListWidget *userListWidget;
    QLabel *nConnectedUsersLabel;

    QVBoxLayout *sidebarLayout;
    QScrollArea *sidebarScrollArea;
    QWidget *sidebarContentWidget;

    QHBoxLayout *mainLayout;
//    QGridLayout *mainLayout;
    QLabel *messageLabel;
//    ChatItem *publicChatLabel;
    QVBoxLayout* scrollableLayout;
    QScrollArea *chatItemScrollArea;
    QWidget *leftColumn;
    QWidget *centerColumn;
    QWidget *rightColumnWidget;

    QStackedWidget *chatStack;
    QWidget *publicChatWidget;
    QScrollArea *chatScrollArea;
    QLabel *chatTitleLabel;
private:
    void createLayout();
    void fillUserListWidget();
    void updateScrollBar();
    void createUserWidget( QGridLayout*);
protected:

signals:

    void chatRoomReady( QColor userColor );
    void messageSent( const QColor colorSender , const QString message );
    void addChatItemRequested(const QString &nickname);
private slots:

    void onClickSendMessage();
    void handleMessageIconClicked(const QString& nickname);
//    void showEvent(QShowEvent *event) override;
    void filterUsers( const QString &text);
    void addChatItem(const QString &nickname);
    void removeChatItem(PrivateChatItem *item);
};


#endif //CHATROOM_CHATROOM_H
