#ifndef SERVERCONFIGDIALOG_H
#define SERVERCONFIGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "include/customLineEdit.h"
#include "server.h"

class ServerDialog : public QDialog {
Q_OBJECT

public:
    ServerDialog(QWidget *parent = nullptr);

private:
    QLabel *ipLabel;
    CustomLineEdit *ipEdit;
    QLabel *portLabel;
    CustomLineEdit *portEdit;
    QPushButton *startServerButton;
    QLabel *titleLabel;
    QLabel *serverStatusLabel;
    QLabel *statusIndicator;
    Server *myServer;

private slots:
    void toggleServer();
    void toggleStyleStatus();
    void validateAddress(const QString &ipAddress);
    void validatePort(const QString &port);
};


#endif // SERVERCONFIGDIALOG_H
