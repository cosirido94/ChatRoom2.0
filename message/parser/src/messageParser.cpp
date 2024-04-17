#include "../include/messageParser.h"

QString MessageParser::extractHeader(const QString &message)
{
    int colonIndex = message.indexOf(':');
    if (colonIndex != -1 )
    {
        return message.left(colonIndex);
    }
    return "";
}

QString MessageParser::extractBody(const QString &message)
{
    int colonIndex = message.indexOf(':');
    if (colonIndex != -1 )
    {
        return message.mid(colonIndex +1 );
    }
    return "";
}