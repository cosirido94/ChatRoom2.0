#include "../include/errorNickMessage.h"

ErrorNickMessage::ErrorNickMessage()
    :header("ERROR_NICK"){}

QString ErrorNickMessage::serialize() const
{
    return header + ":";
}
