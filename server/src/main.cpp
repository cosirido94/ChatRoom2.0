#include <QApplication>
#include "../include/serverDialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QFile styleFile("css/server/style.css");
    /* qDebug() << "Current directory: " << QDir::currentPath(); */

    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream stream(&styleFile);
        QString styleSheet = stream.readAll();

        app.setStyleSheet(styleSheet);

        // Creare e visualizzare il tuo ServerConfigDialog o altre finestre

        ServerDialog dialog;
        dialog.show();

        return app.exec();
    }
    else
    {
        qDebug() << "Errore nell'apertura del file CSS: " << styleFile.errorString();
        return -1;
    }
}
