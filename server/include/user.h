#ifndef CHATROOM_USER_H
#define CHATROOM_USER_H

#include <QString>
#include <QColor>

class User
{
public:
    User(const QString nickname = "" , const QColor color = Qt::black )
    : nickname(nickname) , color(color){}

private:
    QString nickname;
    QColor color;

public:
    QString getNickName() const;
    QColor getColor() const;
    void setNickname( const QString nickname );
    void setColor( const QColor color );
};

#endif //CHATROOM_USER_H
