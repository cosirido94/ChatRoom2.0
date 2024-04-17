#ifndef CHATROOM_CONFIGCHATMESSAGE_H
#define CHATROOM_CONFIGCHATMESSAGE_H

#include "message.h"
#include <QColor>
#include <QTcpSocket>
#include "../server/include/user.h"

class ConfigChatMessage : public Message
{

private:
    QString header;
    QColor color;
    QList <User> userList;

public:
    ConfigChatMessage(const QColor& color, const QList<User>&userList );
    virtual QString serialize() const override;
    static ConfigChatMessage deserialize(const QString& serializedMessage );
    QColor getColor() const;
    QList<User> getUserList() const;
};
#endif //CHATROOM_CONFIGCHATMESSAGE_H
