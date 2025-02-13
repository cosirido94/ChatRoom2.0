#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QEvent>
#include <QDebug>
#include "../include/privateChatItem.h"

PrivateChatItem::PrivateChatItem(const QString &username, QWidget *parent)
    : ChatItem(username , parent )
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

    /*** Segnale per il click del chatItem per aprire la chat ****/
     connect(userNameLabel, &ClickLabel::clicked, this, [=]() {
        qDebug() << "Clicked on:" << username; // Stampa il nome quando viene cliccato
    });

     connect(closeButton , &QPushButton::clicked , this , &PrivateChatItem::onCloseButtonClicked);
}

void PrivateChatItem::enterEvent(QEvent *event)
{
    if (closeButton && !closeButton->isVisible())
    {
        closeButton->setVisible(true);  // Mostra il pulsante di chiusura quando il mouse entra nel widget
    }
    QWidget::enterEvent(event);
}

void PrivateChatItem::leaveEvent(QEvent *event)
{
    if (closeButton && closeButton->isVisible())
    {
        closeButton->setVisible(false);  // Nasconde il pulsante di chiusura quando il mouse esce dal widget
    }
    QWidget::leaveEvent(event);
}

void PrivateChatItem::onCloseButtonClicked()
{
    emit closeRequested(this);
}

void PrivateChatItem::setOnlineStatus(bool isOnline)
{
    QString statusColor = isOnline ? "green" : "red";
    statusOnline->setStyleSheet("background-color: " + statusColor + "; border-radius: 8px;");
}