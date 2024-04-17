#ifndef CHATROOM_ERRORNICKMESSAGE_H
#define CHATROOM_ERRORNICKMESSAGE_H

#include "message.h"

class ErrorNickMessage : public Message
{
private:
    QString header;

public:
    ErrorNickMessage();
    virtual QString serialize() const override;

};
#endif //CHATROOM_ERRORNICKMESSAGE_H
