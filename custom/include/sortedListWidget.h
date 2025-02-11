#ifndef CHATROOM_SORTLISTWIDGET_H
#define CHATROOM_SORTLISTWIDGET_H

#include <QListWidget>
#include <QLabel>

class QTextBrowser;

class SortedListWidget : public QListWidget
{
    Q_OBJECT

public:
    SortedListWidget(QWidget* parent= nullptr);
    void addItem(const QString &nickname , const QString &color );
    void removeItem(const QString &nickname);
    QString getNickname( int index) const;
private:
    void insertItemSorted(QListWidgetItem *item);
    QListWidgetItem* createListWidgetItem(const QString& nickname);
    QWidget* createListItemWidget(const QString &nickname , const QString& color);
    QLabel* createNicknameLabel( const QString &nickname , const QString& color);
    QLabel* createIconLabel( const QString& nickname);
//    void sortList();

signals:
    void messageIconClicked( const QString& nickname);
};
#endif //CHATROOM_SORTLISTWIDGET_H
