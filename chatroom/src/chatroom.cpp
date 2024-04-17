#include "../include/chatroom.h"
#include <QTimer>
ChatRoom* ChatRoom::instance = nullptr;

ChatRoom::ChatRoom(const QString nickname, const QColor userColor, const QList<User> usersList,
       QWidget *parent)
            :nickname(nickname),
             userColor(userColor),
             usersList(usersList)
{
    instance = this;
    setFixedSize(1050, 500);
    setWindowTitle(nickname);

    // Layout principale a griglia con tre colonne
    mainLayout = new QGridLayout(this);

    // Label ChatRoom
    chatRoomLabel = new ClickLabel("ChatRoom", this);
    mainLayout->addWidget(chatRoomLabel, 0, 0, Qt::AlignLeft);

    // Label Message
    messageLabel = new QLabel("Message", this);
    mainLayout->addWidget(messageLabel, 1, 0, Qt::AlignLeft);

    mainLayout->setColumnStretch(0,1);
    // Lista Utenti Connessi
    userListWidget = new SortedListWidget(this);
    mainLayout->addWidget(userListWidget, 2, 2, 1, 1);  // Colonna 2, Row 2


    // Spazio per la Chat Room
    scrollArea = new QScrollArea();
    chatDisplayContainer = new QWidget();
    chatDisplayLayout = new QVBoxLayout();
    chatDisplayContainer->setLayout(chatDisplayLayout);
    chatDisplayContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    scrollArea->setWidget(chatDisplayContainer);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea, 0, 1, 3, 1);  // Colonna 1, Row 0, Span 3 Rows

    // Input Messaggio
    messageInput = new QLineEdit(this);
//    mainLayout->addWidget(messageInput, 3, 1, 1, 1);  // Colonna 1, Row 3

    // Bottone Invio Messaggio
    sendButton = new QPushButton("Send", this);
//    mainLayout->addWidget(sendButton, 3, 2, 1, 1);  // Colonna 2, Row 3
    QHBoxLayout *messageLayout = new QHBoxLayout();
    messageLayout->addWidget(messageInput);
    messageLayout->addSpacing(10);  // Aggiungi uno spazio di 10 pixel tra l'input del messaggio e il bottone
    messageLayout->addWidget(sendButton);

    // Etichetta Utenti Connessi
    connectedUsersLabel = new QLabel("Connected Users: 0", this);
    mainLayout->addWidget(connectedUsersLabel, 0, 2, 1, 1);  // Colonna 2, Row 0

    // Input di Ricerca Utente
    userSearchInput = new QLineEdit(this);
    mainLayout->addWidget(userSearchInput, 1, 2, 1, 1);  // Colonna 2, Row 1

    // Impostazioni del Layout
    mainLayout->setColumnStretch(1, 3);  // Espande la seconda colonna
    mainLayout->setColumnStretch(2, 1);  // Espande la terza colonna
    mainLayout->setHorizontalSpacing(20);
    mainLayout->setVerticalSpacing(10);

    mainLayout->addLayout(messageLayout, 3, 1, 1, 1);  // Colonna 1, Row 3

    // Imposta il layout principale della finestra
    setLayout(mainLayout);


//    mainLayout = new QGridLayout(this);
//
//    scrollArea = new QScrollArea();
//    chatDisplayContainer = new QWidget();
//    chatDisplayLayout = new QVBoxLayout();
//    chatDisplayContainer->setLayout(chatDisplayLayout);
//    chatDisplayContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//    scrollArea->setWidget(chatDisplayContainer);
//    scrollArea->setWidgetResizable(true);
//    mainLayout->addWidget(scrollArea, 0, 0, 6, 4);  // Row: 0, Col: 0, Row Span: 6, Col Span: 4
//
//    messageInput = new QLineEdit(this);
//    mainLayout->addWidget(messageInput, 6, 0, 1, 2);  // Row: 6, Col: 0, Row Span: 1, Col Span: 2
//
//    sendButton = new QPushButton("Send", this);
//    mainLayout->addWidget(sendButton, 6, 2, 1, 2);  // Row: 6, Col: 2, Row Span: 1, Col Span: 2
//
//    connectedUsersLabel = new QLabel("Connected Users: 0", this);
//    mainLayout->addWidget(connectedUsersLabel, 0, 4, 1, 1);  // Row: 0, Col: 4, Row Span: 1, Col Span: 1
//
//    userSearchInput = new QLineEdit(this);
//    mainLayout->addWidget(userSearchInput, 0, 5, 1, 1);  // Row: 0, Col: 5, Row Span: 1, Col Span: 1
//
//    userListWidget = new SortedListWidget(this);
//    mainLayout->addWidget(userListWidget, 1, 4, 6, 1.5);
//
//    mainLayout->setColumnStretch(0, 6);
//    mainLayout->setColumnStretch(4, 1);
//    mainLayout->setHorizontalSpacing(20);
//
//    setLayout(mainLayout);

    connect(sendButton, &QPushButton::clicked, this, &ChatRoom::onClickSendMessage);

//    connect(userSearchInput , &QLineEdit::textChanged , this , &ChatRoom::searchUsers);
    connect(messageInput, &QLineEdit::returnPressed, this, &ChatRoom::onClickSendMessage);

}

ChatRoom *ChatRoom::getInstance()
{
    if(!instance)
    {
        qDebug() << "Errore: Nessuna istanza della ChatRoom è stata creata";
        return nullptr;
    }
    return instance;
}

void ChatRoom::fillUserListWidget()
{
    for (const User &userInfo: usersList)
    {
        QString username = userInfo.getNickName();
        QString color = userInfo.getColor().name();
        userListWidget->addItem(username, color);
    }
}
void ChatRoom::updateNumberClientConnected()
{
    int numUsers = userListWidget->count();
    QString labelText = "Connected Users: " + QString::number(numUsers);
    connectedUsersLabel->setText(labelText);
}

void ChatRoom::onClickSendMessage()
{
    if ( !messageInput->text().isEmpty() )
    {
        QString messageText = messageInput->text();
        emit messageSent(userColor,messageText);
    }
}

void ChatRoom::configureChatRoom()
{
    fillUserListWidget();
    updateNumberClientConnected();

    emit chatRoomReady( userColor );
}

void ChatRoom::appendMessage(MessageWidget *message)
{
    chatDisplayLayout->addWidget(message);
    chatDisplayContainer->updateGeometry();

    messageInput->clear();
    messageInput->setFocus();

    updateScrollBar();
}

void ChatRoom::updateScrollBar()
{
    QTimer::singleShot(0, this, [=]() {
        scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
    });
}

SortedListWidget* ChatRoom::getUserListWidget() const
{
    return userListWidget;
}