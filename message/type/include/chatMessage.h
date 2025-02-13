#ifndef CHATROOM_CHATMESSAGE_H
#define CHATROOM_CHATMESSAGE_H

#include <QDateTime>
#include <QColor>
#include "message.h"

class ChatMessage : public Message
{

public:
    ChatMessage(const QString& sender , const QString& text , const QDateTime& timestamp , const QColor& senderColor);
    virtual ~ChatMessage() = default;

    // Tutti i messaggi visibili sulla Chat devono avere questi metodi
    virtual QString getSender() const = 0;
    virtual QString getText() const = 0;
    virtual QDateTime getTimeStamp() const = 0;
    virtual QColor getSenderColor() const;

protected:
    QString sender;
    QString text;
    QDateTime timestamp;
    QColor senderColor;
};
#endif //CHATROOM_CHATMESSAGE_H
