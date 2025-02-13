#ifndef CHATROOM_PUBLICCHATITEM_H
#define CHATROOM_PUBLICCHATITEM_H

#include "../include/chatItem.h"

class PublicChatItem : public ChatItem
{
    Q_OBJECT

public:
    explicit PublicChatItem(QWidget *parent = nullptr);

};
#endif //CHATROOM_PUBLICCHATITEM_H
