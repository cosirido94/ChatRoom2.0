#ifndef CHATROOM_BROADCASTUSERDISCONNECTEDMESSAGE_H
#define CHATROOM_BROADCASTUSERDISCONNECTEDMESSAGE_H

#include "message.h"
#include <QDateTime>
#include <QColor>

class BroadCastUserDisconnectedMessage : public Message
{

private:
    QString header;
    QString sender;
    QColor colorSender;
    QString userName;
    QColor colorUserName;
    QString text;
    QColor colorText;
    QDateTime timestamp;

public:
    BroadCastUserDisconnectedMessage(const QString userName , const QColor colorUserName );
    virtual QString serialize() const override;
    static BroadCastUserDisconnectedMessage deserialize(const QString& serializedMessage);
    QString getSender() const;
    QColor getColorSender() const;
    QString getUserName() const;
    QColor getColorUserName() const;
    QString getText() const;
    QColor getColorText() const;
    QDateTime getTimeStamp() const;

};
#endif //CHATROOM_BROADCASTUSERDISCONNECTEDMESSAGE_H
