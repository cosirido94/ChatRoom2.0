#include "../include/clientDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QTimer>


void lockInputAccess( CustomLineEdit* , CustomLineEdit* );
void unlockInputAccess( CustomLineEdit* , CustomLineEdit*);

ClientDialog::ClientDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Client Settings");
    setFixedSize(400,275);

    titleLabel = new QLabel("Client Configuration");
    titleLabel->setObjectName("titleLabel");

    ipLabel = new QLabel("Server IP Address:" ,this);
    ipLabel->setObjectName("ipLabel");

    ipEdit = new CustomLineEdit(this);
    ipEdit->setPlaceholderText("Enter IP Address");

    portLabel = new QLabel("Port Number:",this);
    portLabel->setObjectName("portLabel");

    portEdit = new CustomLineEdit(this);
    portEdit->setPlaceholderText("Enter Port Number");

    nickNameLabel = new QLabel("Nickname");
    nickNameLabel->setObjectName("nickNameLabel");

    nickNameEdit = new QLineEdit(this);
    nickNameEdit->setPlaceholderText("Enter Nickname");

    connectButton = new QPushButton("Connect", this);
    connectButton->setObjectName("connectButton");
    connectButton->setFixedSize(250,30);

    progressBar = new QProgressBar(this);  // Aggiungi un nuovo indicatore di progresso
    progressTimer = new QTimer(this);      // Crea un timer

    setProgressBar();
//    int progressValue = 0;

    /* Collegamento click del bottone al alla connect del server
     *
     * */

    connect(ipEdit, SIGNAL(textChanged(const QString &)), this, SLOT(validateAddress(const QString &)));

    connect(portEdit, SIGNAL(textChanged(const QString &)), this, SLOT(validatePort(const QString &)));

    connect(connectButton , &QPushButton::clicked , this , &ClientDialog::connectClicked );
    connect(progressTimer, &QTimer::timeout, this, &ClientDialog::updateProgress);

    /******** Layout *******/

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(ipLabel,ipEdit);
    formLayout->addRow(portLabel,portEdit);
    formLayout->addRow(nickNameLabel,nickNameEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(connectButton);
    buttonLayout->setObjectName("container");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(progressBar);  // Aggiungi l'indicatore di progresso

    setLayout(mainLayout);
}

void ClientDialog::connectClicked()
{
    disableButton();
    if ( ipEdit->getCheckMark() && portEdit->getCheckMark() && getUserName() != "" )
    {
        displayBar();
        progressTimer->start(75);  // Aggiorna ogni 75 millisecondi
    }
    else if ( !ipEdit->getCheckMark() )
    {
        QMessageBox::critical(this, "Error", "Incorrect IP address");
        enableButton();
    }
    else if ( !portEdit->getCheckMark() )
    {
        QMessageBox::critical(this, "Error", "Incorrect port number");
        enableButton();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Nickname missing");
        enableButton();
    }
}

void ClientDialog::updateProgress()
{
    // Simula un progresso fino a 100
    progressValue += 5;
    if (progressValue > 100) {
        progressTimer->stop();

        myClient = new Client(getUserName());
        connect(myClient, &Client::connectionEstablished, this, &ClientDialog::onConnectionEstablished);
        connect(myClient , &Client::connectionError , this , &ClientDialog::onConnectionError);
        connect(myClient , &Client::showMessageClientNotAvailable , this , &ClientDialog::onShowMessageClientNotAvailable);
        myClient->connectToServer(getServerAddress() , getServerPort() );
    }
    else
    {
        progressBar->setValue(progressValue);
        progressBar->setFormat("Please wait, connecting to %1:%2... %p%");
        progressBar->setFormat(progressBar->format().arg(getServerAddress()).arg(QString::number(getServerPort())));
    }
}

void ClientDialog::onConnectionEstablished()
{
//    this->close();
}
void ClientDialog::onConnectionError()
{
    QMessageBox::critical(this, "Error", "Connection failed");

    clearMyClient();

    resetProgressBar();
    displayButton();
    enableButton();
}

void ClientDialog::onShowMessageClientNotAvailable()
{

    QMessageBox::critical(this, "Error", "Nickname already exists");

    clearMyClient();

    resetProgressBar();
    displayButton();
    enableButton();
}

void ClientDialog::clearMyClient()
{
    if (myClient)
    {
        /* Scollego i segnali associati a myClient in clientDialog */

        disconnect(myClient, &Client::connectionEstablished, this, &ClientDialog::onConnectionEstablished);
        disconnect(myClient , &Client::connectionError , this , &ClientDialog::onConnectionError);
        disconnect(myClient , &Client::showMessageClientNotAvailable , this , &ClientDialog::onShowMessageClientNotAvailable);

        /* Chiamo il distruttore di myClient */

        delete myClient;
        myClient = nullptr;
    }
}
void ClientDialog::setProgressBar()
{
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setVisible(false);
    progressValue = 0;
}

void ClientDialog::displayBar()
{
    connectButton->setVisible(false);
    progressBar->setVisible(true);
}

void ClientDialog::displayButton()
{
    connectButton->setVisible(true);
    progressBar->setVisible(false);
}
void ClientDialog::resetProgressBar()
{
    progressValue = 0;
}

void ClientDialog::validateAddress(const QString &ipAddress)
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

void ClientDialog::validatePort(const QString &port)
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


QString ClientDialog::getServerAddress() const
{
    return ipEdit->text();
}

quint16 ClientDialog::getServerPort() const
{
    return portEdit->text().toUShort();
}

QString ClientDialog::getUserName() const
{
    return nickNameEdit->text();
}

void ClientDialog::enableButton()
{
    connectButton->setEnabled(true);
}

void ClientDialog::disableButton()
{
    connectButton->setEnabled(false);
}
