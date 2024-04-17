#include "../include/configChatMessage.h"

ConfigChatMessage::ConfigChatMessage(const QColor &color, const QList<User> &userList)
    :header("CONFIG_CHAT"),
    color(color),
    userList(userList) {}

QColor ConfigChatMessage::getColor() const
{
    return color;
}

QList<User>ConfigChatMessage::getUserList() const
{
    return userList;
}

QString ConfigChatMessage::serialize() const
{
    QString serializedMessage = header + ":" + color.name() + "&&";
    for(const User& user : userList )
    {
        serializedMessage += user.getNickName() + "," + user.getColor().name() + ";;";
    }
    serializedMessage.chop(2);
    return serializedMessage;
}

ConfigChatMessage ConfigChatMessage::deserialize(const QString &serializedMessage)
{
    QString messageWithoutHeader = serializedMessage.section(':',1);
    QStringList parts = messageWithoutHeader.split("&&");

    QString colorString = parts[0];
    QColor userColor(colorString);
    QString userListString = parts[1];

    QStringList userStrings = userListString.split(";;");
    QList<User> usersList;

    for(const QString& userData : userStrings )
    {
        QStringList userDataParts = userData.split(",");

        QString userName = userDataParts[0];
        QString userColorString = userDataParts[1];

        usersList.append(User(userName,QColor(userColorString)) );
    }
    return ConfigChatMessage(userColor , usersList);
}