#ifndef CHATROOM_CHATROOMTEXTMESSAGE_H
#define CHATROOM_CHATROOMTEXTMESSAGE_H

#include "message.h"
#include <QDateTime>
#include <QColor>

class ChatRoomTextMessage : public Message
{

private:
    QString header;
    QString sender;
    QColor colorSender;
    QString text;
    QDateTime timestamp;

public:
    ChatRoomTextMessage(const QString sender , const QColor colorSender , const QString text);
    virtual QString serialize() const override;
    static ChatRoomTextMessage deserialize(const QString& serializedMessage);
    QString getSender() const;
    QColor getColorSender() const;
    QString getText() const;
    QDateTime getTimeStamp() const;
};
#endif //CHATROOM_CHATROOMTEXTMESSAGE_H
