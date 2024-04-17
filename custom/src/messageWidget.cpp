#include "../include/messageWidget.h"

MessageWidget::MessageWidget(const BroadcastUserConnectedMessage &message, QWidget *parent)
    : QFrame(parent)
{
    setupUi();

    QString sender = message.getSender();
    QColor colorSender = message.getColorSender();
    QString userNameConnected = message.getUserName();
    QColor userColorConnected = message.getColorUserName();
    QString text = message.getText();
    QColor colorText = message.getColorText();
    QDateTime timestamp = message.getTimeStamp();

    // Trova il nome utente nel testo del messaggio e formatta il testo di conseguenza
    QString styledText;
    int userNameIndex = text.indexOf(userNameConnected);
    if (userNameIndex != -1)
    {
        // Se il nome utente è presente nel testo, formatta il testo in base al nome utente
        styledText = text.left(userNameIndex);
        styledText += QString("<font color='%1'>%2</font>").arg(userColorConnected.name(), userNameConnected);
        styledText += text.mid(userNameIndex + userNameConnected.length());
    } else
    {
        // Se il nome utente non è presente nel testo, visualizza il testo senza formattazioni aggiuntive
        styledText = text;
    }

    // Imposta i dati del messaggio
    senderLabel->setText(sender);
    textLabel->setText(styledText);
    timestampLabel->setText(timestamp.toString("hh:mm:ss"));

    // Impostazione del colore del sender e del testo del messaggio
    QString styleSender = QString("<font color='%1'>%2</font>").arg(colorSender.name(), sender);
    QString styleText = QString("<font color='%1'>%2</font>").arg(colorText.name(), styledText);

    // Impostazione del testo formattato nei label
    senderLabel->setText(styleSender);
    textLabel->setText(styleText);

    // Applicazione dello stile al widget del messaggio
    QString styleSheet = QString(
            "QWidget#messageWidget {"
            "   background-color: white;"
            "   border-radius: 10px;"
            "}"
    );
    setStyleSheet(styleSheet);
    setObjectName("messageWidget");
}

MessageWidget::MessageWidget(const BroadCastUserDisconnectedMessage &message, QWidget *parent)
    : QFrame(parent)
{
    setupUi();

    QString sender = message.getSender();
    QColor colorSender = message.getColorSender();
    QString userNameConnected = message.getUserName();
    QColor userColorConnected = message.getColorUserName();
    QString text = message.getText();
    QColor colorText = message.getColorText();
    QDateTime timestamp = message.getTimeStamp();

    // Trova il nome utente nel testo del messaggio e formatta il testo di conseguenza
    QString styledText;
    int userNameIndex = text.indexOf(userNameConnected);
    if (userNameIndex != -1)
    {
        // Se il nome utente è presente nel testo, formatta il testo in base al nome utente
        styledText = text.left(userNameIndex);
        styledText += QString("<font color='%1'>%2</font>").arg(userColorConnected.name(), userNameConnected);
        styledText += text.mid(userNameIndex + userNameConnected.length());
    } else
    {
        // Se il nome utente non è presente nel testo, visualizza il testo senza formattazioni aggiuntive
        styledText = text;
    }

    // Imposta i dati del messaggio
    senderLabel->setText(sender);
    textLabel->setText(styledText);
    timestampLabel->setText(timestamp.toString("hh:mm:ss"));

    // Impostazione del colore del sender e del testo del messaggio
    QString styleSender = QString("<font color='%1'>%2</font>").arg(colorSender.name(), sender);
    QString styleText = QString("<font color='%1'>%2</font>").arg(colorText.name(), styledText);

    // Impostazione del testo formattato nei label
    senderLabel->setText(styleSender);
    textLabel->setText(styleText);

    // Applicazione dello stile al widget del messaggio
    QString styleSheet = QString(
            "QWidget#messageWidget {"
            "   background-color: white;"
            "   border-radius: 10px;"
            "}"
    );
    setStyleSheet(styleSheet);
    setObjectName("messageWidget");
}

MessageWidget::MessageWidget(const ChatRoomTextMessage &message, QWidget *parent)
    : QFrame(parent)
{
    setupUi();

    QString sender = message.getSender();
    QColor colorSender = message.getColorSender();
    QString text = message.getText();
    QDateTime timestamp = message.getTimeStamp();

    // Imposta i dati del messaggio
    senderLabel->setText(sender);
    textLabel->setText(text);
    timestampLabel->setText(timestamp.toString("hh:mm:ss"));


    QString styledSender = QString(
            "<font color='%1'>%2</font>"
    ).arg(colorSender.name(), sender );
    senderLabel->setText(styledSender);

    QString styleSheet = QString(
            "QWidget#messageWidget {"
            "   background-color: white;"
            "   border-radius: 10px;"
            "}"
    );
    setStyleSheet(styleSheet);
    setObjectName("messageWidget");
}
void MessageWidget::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Parte superiore del messaggio: mittente e timestamp
    QHBoxLayout* topLayout = new QHBoxLayout();
    senderLabel = new QLabel(this);
    timestampLabel = new QLabel(this);
    topLayout->addWidget(senderLabel);
    topLayout->addStretch();  // Aggiunge spazio elastico per spostare il timestamp a destra
    topLayout->addWidget(timestampLabel);

    // Parte inferiore del messaggio: testo
    textLabel = new QLabel(this);

    // Aggiungi le parti superiori e inferiori al layout principale
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(textLabel);

    setLayout(mainLayout);
}