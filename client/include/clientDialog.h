#ifndef CHATROOM_CLIENTDIALOG_H
#define CHATROOM_CLIENTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>

#include "include/customLineEdit.h"
#include "client.h"

class ClientDialog : public QDialog
{
    Q_OBJECT
public:
    ClientDialog(QWidget *parent = nullptr );
    QString getServerAddress() const;
    quint16 getServerPort() const;
    QString getUserName() const;

private:
    QLabel *titleLabel;
    QLabel *ipLabel;
    CustomLineEdit *ipEdit;
    QLabel *portLabel;
    CustomLineEdit *portEdit;
    QLabel *nickNameLabel;
    QLineEdit *nickNameEdit;
    QPushButton *connectButton;
    QTimer *progressTimer;
    QProgressBar *progressBar;
    int progressValue;
    Client *myClient;

private:
    void setProgressBar();
    void resetProgressBar();
    void displayBar();
    void displayButton();
    void enableButton();
    void disableButton();
    void clearMyClient();

private slots:
    void connectClicked();
    void updateProgress();
    void onConnectionEstablished();
    void onConnectionError();
    void onShowMessageClientNotAvailable();
    void validateAddress( const QString &ipAddress );
    void validatePort( const QString &port );

};

#endif //CHATROOM_CLIENTDIALOG_H
