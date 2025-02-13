#include "../include/chatItem.h"

ChatItem::ChatItem(const QString &chatId, QWidget *parent)
    : QWidget(parent) , chatId(chatId)
{
}

QString ChatItem::getChatId()
{
    return chatId;
}

void ChatItem::updateUnreadMessages(int count)
{
    QString countText = QString::number(count);
    unreadMessageCountLabel->setText(countText);

    int badgeWidth = 30 + (countText.length() -1 ) * 10;
    unreadMessageCountLabel->setFixedSize(badgeWidth,25);
}