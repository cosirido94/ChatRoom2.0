#ifndef CHATROOM_ERRORNICKMESSAGEHANDLER_H
#define CHATROOM_ERRORNICKMESSAGEHANDLER_H

#include "../client/include/clientMessageHandler.h"
#include <QObject>
class ErrorNickMessageHandler : public QObject , public ClientMessageHandler
{
    Q_OBJECT
public:
    ErrorNickMessageHandler() = default;
    virtual void handleMessage(const QString& message);

signals:
    void notifyClient();
};
#endif //CHATROOM_ERRORNICKMESSAGEHANDLER_H
