#ifndef CHATROOM_SORTLISTWIDGET_H
#define CHATROOM_SORTLISTWIDGET_H

#include <QListWidget>

class QTextBrowser;

class SortedListWidget : public QListWidget
{
    Q_OBJECT

public:
    SortedListWidget(QWidget* parent= nullptr);
    void addItem(const QString &nickname , const QString &color );
    void removeItem(const QString &nickname);
    void sortList();
};
#endif //CHATROOM_SORTLISTWIDGET_H
