#include "../include/newUserMessage.h"

NewUserMessage::NewUserMessage(const QString& nickname)
    : header("NEW_USER") , nickname(nickname) {}

QString NewUserMessage::serialize() const
{
    return header + ":" + nickname;
}

QString NewUserMessage::getNickName() const
{
    return nickname;
}