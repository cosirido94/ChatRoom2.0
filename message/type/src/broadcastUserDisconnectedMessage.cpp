#include "../include/broadcastUserDisconnectedMessage.h"
#include <QDebug>

BroadCastUserDisconnectedMessage::BroadCastUserDisconnectedMessage(const QString userName, const QColor colorUserName)
    :header("BROADCAST_USER_DISCONNECTED"),
    sender("/********** SERVER **********/"),
    colorSender(Qt::darkRed),
    userName(userName),
    colorUserName(colorUserName),
    text("User " + userName + " disconnected"),
    colorText(Qt::darkRed),
    timestamp( QDateTime::currentDateTime() ) {}

QString BroadCastUserDisconnectedMessage::serialize() const
{
    return header + ":" + userName + "&&" + colorUserName.name();
}

BroadCastUserDisconnectedMessage BroadCastUserDisconnectedMessage::deserialize(const QString &serializedMessage)
{
    QString messageWithoutHeader = serializedMessage.section(':',1);
    QStringList parts = messageWithoutHeader.split("&&");

    QString userName = parts[0];
    QColor colorUserName(parts[1]);

    return BroadCastUserDisconnectedMessage(userName,colorUserName);
}

QString BroadCastUserDisconnectedMessage::getSender() const
{
    return sender;
}

QColor BroadCastUserDisconnectedMessage::getColorSender() const
{
    return colorSender;
}

QString BroadCastUserDisconnectedMessage::getUserName() const
{
    return userName;
}

QColor BroadCastUserDisconnectedMessage::getColorUserName() const
{
    return colorUserName;
}

QString BroadCastUserDisconnectedMessage::getText() const
{
    return text;
}

QColor BroadCastUserDisconnectedMessage::getColorText() const
{
    return colorText;
}

QDateTime BroadCastUserDisconnectedMessage::getTimeStamp() const
{
    return timestamp;
}