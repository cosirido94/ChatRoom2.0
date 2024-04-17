#ifndef CHATROOM_NEWUSERMESSAGE_H
#define CHATROOM_NEWUSERMESSAGE_H

#include "message.h"

class NewUserMessage : public Message
{
private:
    QString header;
    QString nickname;

public:
    NewUserMessage(const QString& nickname);
    virtual QString serialize() const override;
    static NewUserMessage deserialize(const QString& serializedMessage);
    QString getNickName() const;
};


#endif //CHATROOM_NEWUSERMESSAGE_H
