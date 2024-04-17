#ifndef CHATROOM_BROADCASTUSERCONNECTEDMESSAGE_H
#define CHATROOM_BROADCASTUSERCONNECTEDMESSAGE_H

#include "message.h"
#include <QDateTime>
#include <QColor>

class BroadcastUserConnectedMessage : public Message
{

private:
    QString header;
    QString sender;
    QColor colorSender; /** Sarà il Server ovviamente , specifico il colore **/
    QString userName;
    QColor colorUserName;
    QString text;
    QColor colorText;
    QDateTime timestamp;

public:
    BroadcastUserConnectedMessage(const QString userName , const QColor colorUserName );
    virtual QString serialize() const override;
    static BroadcastUserConnectedMessage deserialize(const QString& serializedMessage);
    QString getSender() const;
    QColor getColorSender() const;
    QString getUserName() const;
    QColor getColorUserName() const;
    QString getText() const;
    QColor getColorText() const;
    QDateTime  getTimeStamp() const;
};
#endif //CHATROOM_BROADCASTUSERCONNECTEDMESSAGE_H
