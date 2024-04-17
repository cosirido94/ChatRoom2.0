#include "../include/broadcastUserConnectedMessage.h"
#include <QDebug>

BroadcastUserConnectedMessage::BroadcastUserConnectedMessage(QString userName, const QColor colorUserName)
    :header("BROADCAST_USER_CONNECTED"),
    sender("/********** SERVER **********/"),
    colorSender(Qt::darkRed),
    userName(userName),
    colorUserName(colorUserName),
    text("User " + userName + " connected"),
    colorText(Qt::darkGreen),
    timestamp( QDateTime::currentDateTime() ) {}

QString BroadcastUserConnectedMessage::serialize() const
{
    return header + ":" + userName + "&&" + colorUserName.name();
}

BroadcastUserConnectedMessage BroadcastUserConnectedMessage::deserialize(const QString &serializedMessage)
{
    QString messageWithoutHeader = serializedMessage.section(':',1);
    QStringList parts = messageWithoutHeader.split("&&");

    QString userName = parts[0];
    QColor colorUserName(parts[1]);

    return BroadcastUserConnectedMessage(userName,colorUserName);
}

QString BroadcastUserConnectedMessage::getSender() const
{
    return sender;
}

QColor BroadcastUserConnectedMessage::getColorSender() const
{
    return colorSender;
}

QString BroadcastUserConnectedMessage::getUserName() const
{
    return userName;
}

QColor BroadcastUserConnectedMessage::getColorUserName() const
{
    return colorUserName;
}

QString BroadcastUserConnectedMessage::getText() const
{
    return text;
}

QColor BroadcastUserConnectedMessage::getColorText() const
{
    return colorText;
}

QDateTime BroadcastUserConnectedMessage::getTimeStamp() const
{
    return timestamp;
}
