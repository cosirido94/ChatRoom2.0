#include "../include/user.h"

QString User::getNickName() const
{
    return nickname;
}

QColor User::getColor() const
{
    return color;
}

void User::setNickname(const QString nickname)
{
    this->nickname = nickname;
}

void User::setColor(const QColor color)
{
    this->color = color;
}