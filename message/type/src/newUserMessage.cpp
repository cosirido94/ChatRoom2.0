#include "../include/newUserMessage.h"
#include <QDebug>
NewUserMessage::NewUserMessage(const QString& nickname)
    : header("NEW_USER") ,
    nickname(nickname) {}

QString NewUserMessage::serialize() const
{
    return header + ":" + nickname;
}

QString NewUserMessage::getNickName() const
{
    return nickname;
}

NewUserMessage NewUserMessage::deserialize(const QString &serializedMessage)
{
    QString messageWithoutHeader = serializedMessage.section(':',1);
    return messageWithoutHeader;
}