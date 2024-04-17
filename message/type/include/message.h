#ifndef CHATROOM_MESSAGE_H
#define CHATROOM_MESSAGE_H

#include <QString>

class Message
{
public:
    virtual QString serialize() const = 0;
    virtual ~Message(){}

};
#endif //CHATROOM_MESSAGE_H
