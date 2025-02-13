#include "../include/chatMessage.h"

ChatMessage::ChatMessage(const QString &sender, const QString &text, const QDateTime &timestamp,const QColor &senderColor)
    :sender(sender) , text(text) , timestamp(timestamp) , senderColor(senderColor)
{}

QString ChatMessage::getSender() const
{
    return sender;
}

QString ChatMessage::getText() const
{
    return text;
}

QDateTime ChatMessage::getTimeStamp() const
{
    return timestamp;
}

QColor ChatMessage::getSenderColor() const
{
    return senderColor;
}