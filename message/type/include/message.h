#ifndef CHATROOM_MESSAGE_H
#define CHATROOM_MESSAGE_H

#include <QString>

class Message
{
public:
    virtual ~Message(){}
    virtual QString serialize() const = 0;

};
#endif //CHATROOM_MESSAGE_H
