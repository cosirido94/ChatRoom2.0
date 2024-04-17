#ifndef CHATROOM_CHATROOMREADYMESSAGE_H
#define CHATROOM_CHATROOMREADYMESSAGE_H

#include "message.h"
#include <QColor>
class ChatRoomReadyMessage : public Message
{

private:
    QString header;
    QString nickname;
    QColor colorNickName;

public:
    ChatRoomReadyMessage(const QString nickname , const QColor colorNickName );
    virtual QString serialize() const override;
    static ChatRoomReadyMessage deserialize(const QString& serializedMessage );
    QString getNickName() const;
    QColor getColor() const;
};

#endif //CHATROOM_CHATROOMREADYMESSAGE_H
