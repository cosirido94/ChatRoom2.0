#ifndef CHATROOM_CONFIGCHATMESSAGEHANDLER_H
#define CHATROOM_CONFIGCHATMESSAGEHANDLER_H

#include "../include/clientMessageHandler.h"
#include "../../../type/include/configChatMessage.h"
#include "../chatroom/include/chatroom.h"
#include <QObject>
class ConfigChatMessageHandler : public QObject , public ClientMessageHandler
{
    Q_OBJECT
public:
    ConfigChatMessageHandler() = default;
    virtual void handleMessage(const QString& message );
    ChatRoom* createChatRoom(const QString nickname,const ConfigChatMessage& configChatMessage);

signals:
    void notifyCloseClientDialog();

};
#endif //CHATROOM_CONFIGCHATMESSAGEHANDLER_H
