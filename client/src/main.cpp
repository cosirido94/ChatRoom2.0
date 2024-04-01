#include <QApplication>
#include <QMetaType>
#include <QFile>
#include "../include/client.h"
#include "../include/clientDialog.h"

#include <iostream>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
//    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    QApplication app(argc, argv);

    QFile styleFile("css/server/style.css");
    /* qDebug() << "Current directory: " << QDir::currentPath();*/

    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream stream(&styleFile);
        QString styleSheet = stream.readAll();

        app.setStyleSheet(styleSheet);

        ClientDialog dialog;
        dialog.show();

        return app.exec();
    }
    else
    {
        qDebug() << "Errore nell'apertura del file CSS: " << styleFile.errorString();
        return -1;
    }
}
