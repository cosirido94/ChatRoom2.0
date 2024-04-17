#include "../include/chatroomTextMessage.h"
#include <QDebug>

ChatRoomTextMessage::ChatRoomTextMessage(const QString sender, const QColor colorSender, const QString text)
    :header("CHATROOM_MESSAGE"),
    sender(sender),
    colorSender(colorSender),
    text(text),
    timestamp( QDateTime::currentDateTime() ){}

QString ChatRoomTextMessage::serialize() const
{
    return header + ":" + sender + "&&" + colorSender.name() + "&&" + text;
}

ChatRoomTextMessage ChatRoomTextMessage::deserialize(const QString &serializedMessage)
{
    QString messageWithoutHeader = serializedMessage.section(':',1);
    QStringList parts = messageWithoutHeader.split("&&");

    QString sender = parts[0];
    QColor colorSender(parts[1]);
    QString text = parts[2];

    return ChatRoomTextMessage(sender,colorSender,text);
}

QString ChatRoomTextMessage::getSender() const
{
    return sender;
}

QColor ChatRoomTextMessage::getColorSender() const
{
    return colorSender;
}

QString ChatRoomTextMessage::getText() const
{
    return text;
}

QDateTime ChatRoomTextMessage::getTimeStamp() const
{
    return timestamp;
}