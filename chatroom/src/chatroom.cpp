#include "../include/chatroom.h"
#include <QTimer>
#include "../custom/include/userWidget.h"
ChatRoom* ChatRoom::instance = nullptr;

ChatRoom::ChatRoom(const QString nickname, const QColor userColor, const QList<User> usersList,
       QWidget *parent)
            : QWidget(parent),
             nickname(nickname),
             userColor(userColor),
             usersList(usersList)
{
    instance = this;
    createLayout();

    connect(userSearchInput, &QLineEdit::textChanged, this, &ChatRoom::filterUsers);
    connect(userListWidget, &SortedListWidget::messageIconClicked, this, &ChatRoom::handleMessageIconClicked);
    connect(this , &ChatRoom::addChatItemRequested , this , &ChatRoom::addChatItem);
    connect(sendButton , &QPushButton::clicked , this , &ChatRoom::onClickSendMessage);
    connect(messageInput, &QLineEdit::returnPressed, this, &ChatRoom::onClickSendMessage);
}


void ChatRoom::createLayout()
{
    setFixedSize(1050, 500);
    setWindowTitle(nickname);

    // 1. Contenitore principale per la colonna sinistra
    leftColumn = new QWidget;

    QVBoxLayout *leftLayout = new QVBoxLayout(leftColumn);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(0);  // Rimuove margini extra

    // 2. Etichetta "Messaggi" in alto (fissa)
    QLabel *messageLabel = new QLabel("Messages");
    messageLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
//    messageLabel->setStyleSheet("font-weight: bold;");
    messageLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: #333333; padding: 8px; background-color: #f2f2f2;");  // Aggiungi font, colore, padding e sfondo
    leftLayout->addWidget(messageLabel);

    // 3. Etichetta "#public" sotto "Messaggi" (fissa)
    ChatItem *publicChatLabel = new ChatItem(this);
//    publicChatLabel->setStyleSheet("border: 2px solid black; padding:5px;");
    leftLayout->addWidget(publicChatLabel);

    // 4. Spazio extra opzionale, se vuoi aumentare leggermente la distanza tra `#public` e i `ChatItem`
//    leftLayout->addSpacing(10);  // Distanza fissa opzionale

    // 5. Creazione della QScrollArea per i ChatItem dinamici
    chatItemScrollArea = new QScrollArea;
    chatItemScrollArea->setWidgetResizable(true);
    chatItemScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    chatItemScrollArea->setStyleSheet("QScrollArea { border: none; }");

    // 6. Contenitore e layout per l'area di scroll dei ChatItem
    QWidget *scrollableArea = new QWidget;
    scrollableLayout = new QVBoxLayout(scrollableArea);
    scrollableLayout->setSpacing(10);  // Spaziatura costante tra ChatItem
    scrollableLayout->setAlignment(Qt::AlignTop);  // ChatItem si inseriscono dall'alto
    scrollableLayout->setContentsMargins(0, 0, 0, 0);  // Rimuove margini che potrebbero alterare l'allineamento
    scrollableArea->setLayout(scrollableLayout);

    chatItemScrollArea->setWidget(scrollableArea);

    // 7. Aggiungiamo l'area di scroll alla colonna sinistra
    leftLayout->addWidget(chatItemScrollArea);

    // 8. Imposta larghezza fissa della colonna sinistra
    leftColumn->setFixedWidth(250);


    // 9. Integra la colonna sinistra nel layout principale
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(leftColumn);

    mainLayout->setSpacing(0);

    /******** 2 COLONNA ******** */

    centerColumn = new QWidget;
    QVBoxLayout *centerColumnLayout = new QVBoxLayout(centerColumn);
    centerColumnLayout->setContentsMargins(10, 10, 10, 10);
    centerColumnLayout->setSpacing(5); // Distanza tra gli elementi

    /********* Intestazione della Chat Attiva *********/
    chatTitleLabel = new QLabel("# Public Chat");
    chatTitleLabel->setAlignment(Qt::AlignCenter);
    chatTitleLabel->setStyleSheet("font-weight: bold; font-size: 16px; background-color: #e0e0e0; padding: 8px; border-radius: 5px;");

/********* Contenitore della Chat (Bordo visibile) *********/
    QWidget *chatContainer = new QWidget;
    QVBoxLayout *chatContainerLayout = new QVBoxLayout(chatContainer);
    chatContainerLayout->setContentsMargins(5, 5, 5, 5);
    chatContainerLayout->setSpacing(0);

    chatContainer->setStyleSheet("border: 2px solid #cccccc; border-radius: 5px; ");

    chatStack = new QStackedWidget(this);
    chatStack->setStyleSheet("border: none; background-color: #e0e0e0;");
    publicChatWidget = new QWidget;

    QVBoxLayout *chatLayout = new QVBoxLayout(publicChatWidget);
    chatLayout->setContentsMargins(0, 0, 0, 0);
    chatLayout->setSpacing(0);

// 🔥 Rimuoviamo il bordo della QScrollArea!
    chatScrollArea = new QScrollArea;
    chatScrollArea->setWidgetResizable(true);
    chatScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    chatScrollArea->setStyleSheet("border: none; background: transparent;"); // ❌ Niente bordo visibile
    chatScrollArea->setFrameStyle(QFrame::NoFrame);

    QWidget *messageContainer = new QWidget;
    QVBoxLayout *publicChatLayout = new QVBoxLayout(messageContainer);
    publicChatLayout->setAlignment(Qt::AlignTop);
    publicChatLayout->setSpacing(10);

    chatScrollArea->setWidget(messageContainer);
    chatLayout->addWidget(chatScrollArea);
    publicChatWidget->setLayout(chatLayout);

    chatStack->addWidget(publicChatWidget);

/********* Input e Pulsante *********/

    messageInput = new QLineEdit;
    messageInput->setPlaceholderText("Text a message...");
    messageInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    messageInput->setFixedHeight(40);

    sendButton = new QPushButton("Send");
    sendButton->setFixedSize(80, 40);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);



    chatContainerLayout->addWidget(chatStack);
    chatContainer->setLayout(chatContainerLayout);

    centerColumnLayout->addWidget(chatTitleLabel, 0);
    centerColumnLayout->addWidget(chatContainer, 1);
    centerColumnLayout->addLayout(inputLayout, 0);

    centerColumn->setLayout(centerColumnLayout);
    mainLayout->addWidget(centerColumn);

    /******** 3 COLONNA ******** */

    QVBoxLayout *rightColumnLayout = new QVBoxLayout;
    rightColumnLayout->setContentsMargins(10, 10, 10, 10);
    rightColumnLayout->setSpacing(10);

    // Label con numero utenti connessi
    nConnectedUsersLabel = new QLabel("Connected Users: 0");
    nConnectedUsersLabel->setStyleSheet("font-weight: bold;");
    rightColumnLayout->addWidget(nConnectedUsersLabel);

    // Input di ricerca
    userSearchInput = new QLineEdit();
    userSearchInput->setPlaceholderText("Search user...");
    userSearchInput->setFixedHeight(30);
    rightColumnLayout->addWidget(userSearchInput);

    // SortedListWidget con scroll
    userListWidget = new SortedListWidget();
    userListWidget->setStyleSheet("background-color: #ffffff; border: 1px solid #cccccc;");
//    userListWidget->setFixedHeight(300);
//    userListWidget->setFixedWidth(200);

    // Popolazione di test per la lista utenti
//    for (int i = 1; i <= 30; ++i) {
//        QString nickname = QString("User %1").arg(i);
//        QString color = (i % 2 == 0) ? "#FF0000" : "#0000FF";  // Rosso e blu alternati per testare il layout visivo
//        userListWidget->addItem(nickname, color);
//    }
    fillUserListWidget();
    // Aggiungi QScrollArea per il controllo dello scroll
    scrollUserWidgetArea = new QScrollArea;
    scrollUserWidgetArea->setWidget(userListWidget);
    scrollUserWidgetArea->setWidgetResizable(true);
    scrollUserWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollUserWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollUserWidgetArea->setFixedWidth(150);
    scrollUserWidgetArea->setStyleSheet("QScrollArea { border: none; }");
    rightColumnLayout->addWidget(scrollUserWidgetArea);

    // Aggiungi layout della colonna di destra al widget placeholder
    rightColumnWidget = new QWidget;
    rightColumnWidget->setLayout(rightColumnLayout);
    rightColumnWidget->setStyleSheet("background-color: #f0f0f0;");
    rightColumnWidget->setFixedWidth(250);
//    rightColumnWidget->setFixedWidth(250);
    mainLayout->addWidget(rightColumnWidget);

    // Imposta il layout principale
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    QTimer::singleShot(2000, this, [this]()
    {
        qDebug() << leftColumn->size();
        qDebug() << centerColumn->size();
        qDebug() << rightColumnWidget->size();
        qDebug() << this->size();
        qDebug() << this->sizeHint();
    });
}


//void ChatRoom::createUserWidget( QGridLayout* layout)
//{
//    // Creare un layout verticale per contenere gli UserWidget
//    QVBoxLayout *userWidgetsLayout = new QVBoxLayout();
//    userWidgetsLayout->setAlignment(Qt::AlignTop); // Allineare i widget in alto
//
//    // Aggiungi gli UserWidget al layout verticale
//    for (int i = 0; i < 20; ++i) {
//        UserWidget *userWidget = new UserWidget("Cosimo", this);
//        userWidgetsLayout->addWidget(userWidget);
//    }
//
//    // Creare un widget per contenere il layout verticale degli UserWidget
//    QWidget *userWidgetsContainer = new QWidget();
//    userWidgetsContainer->setLayout(userWidgetsLayout);
//
//    // Creare un'area di scorrimento e impostare il suo widget visualizzabile
//    QScrollArea *scrollArea = new QScrollArea();
//    scrollArea->setWidgetResizable(true); // Il widget interno può essere ridimensionato
//    scrollArea->setWidget(userWidgetsContainer);
//
//    // Aggiungi lo scrollArea al layout principale
//    mainLayout->addWidget(scrollArea, 1, 0, Qt::AlignTop | Qt::AlignLeft);
//}
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

void ChatRoom::chatroomReadyNotify()
{
    emit chatRoomReady(userColor);
}
void ChatRoom::appendMessage(MessageWidget *message)
{
    chatDisplayLayout->addWidget(message);
    chatDisplayContainer->updateGeometry();

    messageInput->clear();
    messageInput->setFocus();

    updateScrollBar();
}


SortedListWidget* ChatRoom::getUserListWidget() const
{
    return userListWidget;
}

void ChatRoom::updateUserList(QString nickname, QColor colorUsername, bool op)
{
    QString colorString = colorUsername.name();
    if (op) /* voglio aggiungere op == true */
    {
        userListWidget->addItem(nickname,colorString);
    }
    else /* voglio rimuovere op == false */
    {
        userListWidget->removeItem(nickname);
    }
}

void ChatRoom::updateNumberClientConnected()
{
    int numUsers = userListWidget->count();
    QString labelText = "Connected Users: " + QString::number(numUsers);
    nConnectedUsersLabel->setText(labelText);
}

void ChatRoom::filterUsers(const QString &text)
{
    for(int i = 0 ; i < userListWidget->count() ; ++i )
    {
        QString username = userListWidget->getNickname(i);
        if(username.startsWith(text, Qt::CaseInsensitive))
        {
            userListWidget->item(i)->setHidden(false);
        }
        else
        {
            userListWidget->item(i)->setHidden(true);
        }
    }
}

void ChatRoom::handleMessageIconClicked(const QString &nickname)
{
    qDebug() << "Click detected! user " << nickname;

    emit addChatItemRequested(nickname);
}

void ChatRoom::addChatItem(const QString &nickname)
{
    if (nickname == ChatRoom::getNickname())
    {
        qDebug() << "Non puoi aggiungere una chat con te stesso!";
        return;
    }

    for (int i = 0; i < scrollableLayout->count(); ++i)
    {
        QWidget *widget = scrollableLayout->itemAt(i)->widget();
        if (ChatItem *chatItem = qobject_cast<ChatItem *>(widget))
        {
            if (chatItem->getUserName() == nickname )
            {
                qDebug() << "ChatItem con nickname" << nickname << "esiste già!";
                return;
            }
        }
    }

    ChatItem *chatUser = new ChatItem(nickname);
    chatUser->setFixedHeight(30);

    connect(chatUser , &ChatItem::closeRequested , this , &ChatRoom::removeChatItem);
    scrollableLayout->addWidget(chatUser);
}

void ChatRoom::removeChatItem(ChatItem *item)
{
    if(!item) return;

    qDebug() << "Removing ChatItem: " << item->objectName();

    scrollableLayout->removeWidget(item);
    item->deleteLater();
}

void ChatRoom::updateChatItemStatus(const QString &nickname, bool isOnline)
{
    for (int i = 0; i < scrollableLayout->count(); ++i)
    {
        QWidget *widget = scrollableLayout->itemAt(i)->widget();
        if (ChatItem *chatItem = qobject_cast<ChatItem *>(widget))
        {
            if (chatItem->getUserName() == nickname)
            {
                chatItem->setOnlineStatus(false);
                return;
            }
        }
    }
}

void ChatRoom::appendNewMessage(const ChatRoomTextMessage &message)
{

    // Crea il widget per il messaggio
    MessageWidget *messageWidget = new MessageWidget(message);

    // Aggiungi il MessageWidget al layout della chat
    QWidget *messageContainer = chatScrollArea->widget();
    QVBoxLayout *messageLayout = qobject_cast<QVBoxLayout*>(messageContainer->layout());
    if (messageLayout)
    {
        messageLayout->addWidget(messageWidget);
    }

    // Scroll verso il basso
    chatScrollArea->updateGeometry();
    updateScrollBar();
}

void ChatRoom::onClickSendMessage()
{
    QString messageText = messageInput->text();
    if (!messageText.isEmpty())
    {
        emit messageSent(userColor,messageText);
        messageInput->clear();
    }
}

void ChatRoom::updateScrollBar()
{
    QTimer::singleShot(50, this, [=]()
    {
        chatScrollArea->verticalScrollBar()->setValue(chatScrollArea->verticalScrollBar()->maximum());
    });
}

QString ChatRoom::getNickname()
{
    return nickname;
}