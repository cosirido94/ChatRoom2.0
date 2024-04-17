#include "../include/chatroomReadyMessage.h"
#include <QDebug>

ChatRoomReadyMessage::ChatRoomReadyMessage(const QString nickname, const QColor colorNickName )
    : header("CHATROOM_READY") ,
    nickname(nickname) ,
    colorNickName(colorNickName) {}

QString ChatRoomReadyMessage::serialize() const
{
    return header + ":" + nickname + "&&" + colorNickName.name();
}

ChatRoomReadyMessage ChatRoomReadyMessage::deserialize(const QString &serializedMessage)
{
    QString messageWithoutHeader = serializedMessage.section(':',1);
    QStringList parts = messageWithoutHeader.split("&&");

    QString nickname = parts[0];
    QColor colorNickName(parts[1]);

    return ChatRoomReadyMessage(nickname,colorNickName);
}

QString ChatRoomReadyMessage::getNickName() const
{
    return nickname;
}

QColor ChatRoomReadyMessage::getColor() const
{
    return colorNickName;
}