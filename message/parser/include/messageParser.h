
#ifndef CHATROOM_MESSAGEPARSER_H
#define CHATROOM_MESSAGEPARSER_H

#include <QString>
class MessageParser
{
public:
    static QString extractHeader(const QString& message);
    static QString extractBody(const QString& message);
};

#endif //CHATROOM_MESSAGEPARSER_H
