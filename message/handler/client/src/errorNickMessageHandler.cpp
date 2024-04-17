#include "../include/errorNickMessageHandler.h"
#include <qdebug.h>
void ErrorNickMessageHandler::handleMessage(const QString &message)
{
    qDebug() << "Qui viene gestito il messaggio di errore";
    emit notifyClient();
}