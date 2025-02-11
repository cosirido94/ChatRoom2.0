#include "../include/chatItem.h"
#include <QDebug>
#include <QTimer>

ChatItem::ChatItem(QWidget *parent)
    : QWidget(parent) , username("#public")
{
    /**  Creazione della label #public  **/

    userNameLabel = new ClickLabel(this);
    userNameLabel->setText(username);

    /* Il widget non si adatta alle dimensioni del contenitore
     * ne in altezza ne in lunghezza ->setStylePolicy(Fixed,Fixed) */
    userNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    userNameLabel->setStyleSheet("font-weight: bold;"
                                 "color: black;"
                                 "font-size:16px;");

    /** Creazione del contatore di messaggi non letti chat pubblica  **/
    unreadMessageCountLabel = new QLabel("0", this);

    /* Calcolo della dimensione di unread (rettangolo)
     * all'inizializzazione di "0" */

    QString countText = "0";
    int badgeWidth = 30 + (countText.length() - 1) * 10;  // Inizia con 30px e aggiunge 10px per ogni cifra in più
    unreadMessageCountLabel->setFixedSize(badgeWidth, 25);
    unreadMessageCountLabel->setText(countText);

    /* Queste righe ci serviranno dopo
     * QString countText = (0 > 999) ? "999+" : QString::number(0);
     * unreadMessageCountLabel->setText(countText); */

    unreadMessageCountLabel->setStyleSheet(
            "background-color: blue;"
            "color: white;"
            "border-radius: 12px;"
            "font-weight: bold;"
            "font-size: 16px;"
            "padding: 2px;"
    );

    /* Serve per centrare il numero dentro al rettangolo */
    unreadMessageCountLabel->setAlignment(Qt::AlignCenter);

    /** Creazione del contenitore (QWidget) che conterrà #public e #unread **/
    QWidget *container = new QWidget(this);

    /** Creo il layout per i 2 widget e lo associo al container
     * Quando verranno aggiunti #public e unread questi diventeranno
     * figli di container e il layout gestirà il loro posizionamento **/
    QHBoxLayout *layout = new QHBoxLayout(container);

    /* Imposto una larghezza fissa perchè sennò l'allineamento tra gli widget
     * viene sballato e la distanza non di 20px tra loro perchè ha prende più spazio tra
     * loro (perchè lo trova) del dovuto */
    container->setFixedWidth(180);
    container->setStyleSheet("");

    /* Serve per posizionare #public a distanza 10px da sinistra mettendo un margin left */
    layout->setContentsMargins(10, 0, 0, 0); // Margine sinistro di 15px

    /* Imposta la distanza tra i 2 widget: 20px */
    layout->setSpacing(20);

    /* Aggiunta widget al layout -> devo mettere AlignLeft per allinearli a sinistra */
    layout->addWidget(userNameLabel,0, Qt::AlignLeft);
    layout->addWidget(unreadMessageCountLabel,0,Qt::AlignLeft);

    /** Creo layout principale per gestire container e il tutto correttamente **/
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Margini esterni del widget ChatItem
    mainLayout->addWidget(container);

    setLayout(mainLayout);

    /* Utili impostazioni di Debugging dopo che finestra è stata creata */
    /*    QTimer::singleShot(2000, this, [this]()
     *    {
            qDebug() << "ChatItem (container) size after 2 seconds: " << this->size();
            qDebug() << "unreadMessageCountLabel size after 2 seconds: " << unreadMessageCountLabel->size();
            qDebug() << "#public label size after 2 seconds: " << userNameLabel->size();
            qDebug() << "userNameLabel position: " << userNameLabel->pos();
            qDebug() << "unreadMessageCountLabel position: " << unreadMessageCountLabel->pos();
            qDebug() << "userNameLabel width: " << userNameLabel->width();
            qDebug() << "unreadMessageCountLabel width: " << unreadMessageCountLabel->width();
           });
   */
}

ChatItem::ChatItem(const QString &username , QWidget *parent)
    : QWidget(parent) , username(username)
{
    setMouseTracking(true);

    statusOnline = new QLabel;
    statusOnline->setFixedSize(16, 16);
//    statusOnline->setObjectName("statusOnline");
    QString statusColor = "green";
    statusOnline->setStyleSheet("background-color: " + statusColor + "; border-radius: 8px; }");

    userNameLabel = new ClickLabel(this);
    userNameLabel->setText(username);
    userNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    userNameLabel->setFixedWidth(100);


    userNameLabel->setStyleSheet("font-weight: bold;"
                                 "color: black;"
                                 "font-size:16px;");

    unreadMessageCountLabel = new QLabel("0", this);

    QString countText = "0";
    int badgeWidth = 30 + (countText.length() - 1) * 10;  // Inizia con 30px e aggiunge 10px per ogni cifra in più
    unreadMessageCountLabel->setFixedSize(badgeWidth, 25);
    unreadMessageCountLabel->setText(countText);

    unreadMessageCountLabel->setStyleSheet(
            "background-color: blue;"
            "color: white;"
            "border-radius: 12px;"
            "font-weight: bold;"
            "font-size: 16px;"
            "padding: 2px;"
    );

    unreadMessageCountLabel->setAlignment(Qt::AlignCenter);

    closeButton = new QPushButton("X");
    closeButton->setFixedSize(20,20);
    closeButton->setStyleSheet("QPushButton { border: none; color: gray; font-size: 16px;}"
                               "QPushButton:hover { color: red; }"
                               "QLabel { margin-right: 0px; }");
    closeButton->setVisible(false);

    QWidget *container = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(container);

    container->setFixedWidth(220);
    container->setStyleSheet("border: 2px solid red");

    layout->setContentsMargins(10, 0, 0, 0); // Margine sinistro di 15px
//    layout->setSpacing(20);

    layout->addWidget(statusOnline,0, Qt::AlignLeft);
    layout->addSpacing(5);
    layout->addWidget(userNameLabel,0, Qt::AlignLeft);
    layout->addSpacing(20);
    layout->addWidget(unreadMessageCountLabel ,0, Qt::AlignLeft);
    layout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    layout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Margini esterni del widget ChatItem
    mainLayout->addWidget(container);

    setLayout(mainLayout);

//    createWidgets();
//    createLayout();

    /*** Segnale per il click del chatItem per aprire la chat ****/
    connect(userNameLabel, &ClickLabel::clicked, this, [=]() {
        qDebug() << "Clicked on:" << username; // Stampa il nome quando viene cliccato
    });

    connect(closeButton , &QPushButton::clicked , this , &ChatItem::onCloseButtonClicked);
}

void ChatItem::createWidgets()
{
    setMouseTracking(true);

    userNameLabel = new ClickLabel(this);
    userNameLabel->setText(username);
    userNameLabel->setStyleSheet("font-weight: bold; color: black;");
    userNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    statusOnline = new QLabel;
    statusOnline->setFixedSize(16, 16);
    statusOnline->setObjectName("statusOnline");
    QString statusColor = "green";
    statusOnline->setStyleSheet("QLabel#statusOnline { background-color: " + statusColor + "; border-radius: 8px; }");

    unreadMessageCountLabel = new QLabel("0");
    unreadMessageCountLabel->setStyleSheet("margin-left: 40px;");

    closeButton = new QPushButton("X");
    closeButton->setFixedSize(20,20);
    closeButton->setStyleSheet("QPushButton { border: none; color: gray;}"
                               "QPushButton:hover { color: red; }"
                               "QLabel { margin-right: 0px; }");
    closeButton->setVisible(false);
}

void ChatItem::createLayout()
{
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(statusOnline);
    layout->addWidget(userNameLabel);

    layout->addWidget(unreadMessageCountLabel);

    QSpacerItem *spacer = new QSpacerItem(1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(spacer);

    layout->addWidget(closeButton,0 , Qt::AlignRight);

    layout->setContentsMargins(5,5,5,5);
    setLayout(layout);
}

void ChatItem::enterEvent(QEvent *event)
{
    if (closeButton)
    {
        if (!closeButton->isVisible())
        {
            closeButton->setVisible(true);
        }
    }
//    else
//    {
//        qDebug() << "closeButton is nullptr in enterEvent!";
//    }
    QWidget::enterEvent(event);
}

void ChatItem::leaveEvent(QEvent *event)
{
    if (closeButton)
    {
        if (closeButton->isVisible())
        {
            closeButton->setVisible(false);
        }
    }
//    else
//    {
//        qDebug() << "closeButton is nullptr in leaveEvent!";
//    }
    QWidget::leaveEvent(event);
}

void ChatItem::onCloseButtonClicked()
{
    emit closeRequested(this);
}

QString ChatItem::getUserName()
{
    return username;
}
void ChatItem::setOnlineStatus(bool isOnline)
{
    QString statusColor = isOnline ? "green" : "red";
    statusOnline->setStyleSheet("background-color: " + statusColor + "; border-radius: 8px;");
}