
#include "../include/serverDialog.h"
#include "include/customLineEdit.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <qdebug.h>
#include <QMessageBox>

/* #include "../include/MyServer.h" */

void lockInputAccess( CustomLineEdit* , CustomLineEdit* );
void unlockInputAccess( CustomLineEdit* , CustomLineEdit*);
void toggleStatus( QPushButton * , QLabel *);

ServerDialog::ServerDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Server Settings");
    setFixedSize(400, 250);

    titleLabel = new QLabel("Server Configuration");
    titleLabel->setObjectName("titleLabel");

    ipLabel = new QLabel("Server IP Address:", this);
    ipLabel->setObjectName("ipLabel");

    ipEdit = new CustomLineEdit(this);
    ipEdit->setPlaceholderText("Enter IP Address");

    portLabel = new QLabel("Port Number:", this);
    portLabel->setObjectName("portLabel");

    portEdit = new CustomLineEdit(this);
    portEdit->setPlaceholderText("Enter Port Number");

    serverStatusLabel = new QLabel("Server status");
    serverStatusLabel->setObjectName("serverStatusLabel");

    statusIndicator = new QLabel;
    statusIndicator->setFixedSize(16, 16);  // Set the size of the indicator
    statusIndicator->setObjectName("statusIndicator");
    statusIndicator->setStyleSheet("QLabel#statusIndicator { background-color: red; border-radius: 8px; }");

    startServerButton = new QPushButton("Start Server", this);
    startServerButton->setObjectName("serverButton");
    startServerButton->setFixedSize(250,30);

    /* Collego il click del bottone all'avvio o a fermare il server */

    connect(startServerButton, &QPushButton::clicked, this, &ServerDialog::toggleServer);
    connect(ipEdit, SIGNAL(textChanged(const QString &)), this, SLOT(validateAddress(const QString &)));
    connect(portEdit, SIGNAL(textChanged(const QString &)), this, SLOT(validatePort(const QString &)));

    /******** Layout *******/

    /* Layout della form */


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(ipEdit);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(portEdit);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(ipLabel, layout);
    formLayout->addRow(portLabel, portEdit);
    formLayout->addRow(serverStatusLabel , statusIndicator);

    /* Layout per il bottone (un container che lo contiene e poi si centra da solo */

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startServerButton);
    buttonLayout->setObjectName("container");

    /* Creo l'intero layout dell'interfaccio creando un mainLayout a cui aggiungo tutti gli widget */

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void ServerDialog::toggleServer()
{
    if ( ipEdit->getCheckMark() && portEdit->getCheckMark() && myServer == nullptr ) {
        unlockInputAccess(ipEdit, portEdit);
        toggleStyleStatus();

        QString ip = ipEdit->text();
        QString port = portEdit->text();

        myServer = new Server(ip, port.toUShort());
    }
    else if ( !ipEdit->getCheckMark() )
    {
        QMessageBox::critical(this,"Error","Incorrect IP address ");
    }
    else if (ipEdit->getCheckMark() && !portEdit->getCheckMark() )
    {
        QMessageBox::critical(this,"Error","Incorrect port number");
    }
    else
    {
        lockInputAccess(ipEdit , portEdit );
        toggleStyleStatus();

        /* *Andranno anche chiuse le connessioni */
        clearServer();
    }
}

void ServerDialog::validateAddress(const QString &ipAddress)
{
    QRegExp ipRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    bool isValid = ipRegex.exactMatch(ipAddress);

    ipEdit->getIndicatorLabel();

    if(isValid)
    {
        ipEdit->getIndicatorLabel()->setPixmap(QPixmap("img/check-mark"));
        ipEdit->setCheckMark(true);
    }
    else
    {
        ipEdit->getIndicatorLabel()->setPixmap(QPixmap("img/cross-mark"));
        ipEdit->setCheckMark(false);
    }
}

void ServerDialog::validatePort(const QString &port)
{
    QRegExp portRegex("^([1-9]\\d{0,3}|[1-5]\\d{4}|6[0-5][0-5][0-3][0-5])$");
    bool isValid = portRegex.exactMatch(port);

    portEdit->getIndicatorLabel();

    if(isValid)
    {
        portEdit->getIndicatorLabel()->setPixmap(QPixmap("img/check-mark"));
        portEdit->setCheckMark(true);
    }
    else
    {
        portEdit->getIndicatorLabel()->setPixmap(QPixmap("img/cross-mark"));
        portEdit->setCheckMark(false);
    }
}

void ServerDialog::toggleStyleStatus()
{
    if ( !myServer )
    {
        startServerButton->setText("Stop Server");
        startServerButton->setStyleSheet("background-color: red;");
        statusIndicator->setStyleSheet("QLabel#statusIndicator { background-color: green; border-radius: 8px; }");
    }
    else
    {
        startServerButton->setText("Start Server");
        startServerButton->setStyleSheet("background-color: green");
        statusIndicator->setStyleSheet("QLabel#statusIndicator { background-color: red; border-radius: 8px; }");
    }
}

void ServerDialog::clearServer()
{
    delete myServer;
    myServer = nullptr;
}

void lockInputAccess( CustomLineEdit *ipEdit , CustomLineEdit *portEdit )
{
    ipEdit->setReadOnly(false);
    portEdit->setReadOnly(false);
}

void unlockInputAccess( CustomLineEdit *ipEdit , CustomLineEdit *portEdit )
{
    ipEdit->setReadOnly(true);
    portEdit->setReadOnly(true);
}
