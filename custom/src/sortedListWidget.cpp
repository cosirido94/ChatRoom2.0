#include "../include/sortedListWidget.h"
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

SortedListWidget::SortedListWidget(QWidget *parent) : QListWidget(parent)
{
//    this->setSortingEnabled(true);
//    sortList();
}

void SortedListWidget::addItem(const QString &nickname, const QString &color)
{
    QIcon messageIcon("img/message-icon.png");
    QPixmap pixmap = messageIcon.pixmap(QSize(20, 20));

    // Create a widget to hold the user name and message icon
    QWidget* listItemWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(listItemWidget);

    // Create a label for the user name
    QLabel* nameLabel = new QLabel(nickname);
    nameLabel->setStyleSheet(QString("color: %1;").arg(color));

    // Create a label for the message icon
    QLabel* iconLabel = new QLabel();
    iconLabel->setPixmap(pixmap);

    // Add the user name label and message icon label to the layout
    layout->addWidget(nameLabel);
    layout->addSpacing(10); // Add some spacing between the user name and the message icon
    layout->addWidget(iconLabel);

    // Set the layout margins
    layout->setContentsMargins(0, 0, 0, 0);

    // Create a new list item
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(100, 30)); // Set the size of the list item

    // Insert the new item into the list widget
    int index = 0;
    while (index < count() && this->item(index)->text() < nickname)
    {
        ++index;
    }
    insertItem(index, item);
    setItemWidget(item, listItemWidget);

    // Update the list widget
    update();

    qDebug() << "Lista utenti dopo l'aggiunta di" << nickname << ":";
    for (int i = 0; i < count(); ++i) {
        if (this->item(i)) {
            qDebug() << "Elemento" << i << ":" << this->item(i)->text();
        } else {
            qDebug() << "Elemento" << i << ": null";
        }
    }

//    QIcon messageIcon("img/message-icon.png");
//    QPixmap pixmap = messageIcon.pixmap(QSize(20, 20));
//
//    // Create a widget to hold the user name and message icon
//    QWidget* listItemWidget = new QWidget();
//    QHBoxLayout* layout = new QHBoxLayout(listItemWidget);
//
//    // Create a label for the user name
//    QLabel* nameLabel = new QLabel(nickname);
//    nameLabel->setStyleSheet(QString("color: %1;").arg(color));
//
//    // Create a label for the message icon
//    QLabel* iconLabel = new QLabel();
//    iconLabel->setPixmap(pixmap);
//
//    // Add the user name label and message icon label to the layout
//    layout->addWidget(nameLabel);
//    layout->addSpacing(10); // Add some spacing between the user name and the message icon
//    layout->addWidget(iconLabel);
//
//    // Set the layout margins
//    layout->setContentsMargins(0, 0, 0, 0);
//
//    // Create a new list item
//    QListWidgetItem* item = new QListWidgetItem(nickname);
//    item->setSizeHint(QSize(100, 30)); // Set the size of the list item
//
//    // Insert the new item into the list widget
//    int index = 0;
//    while (index < count() && this->item(index)->text() < nickname  )
//    {
//        ++index;
//    }
//    insertItem(index, item);
//    setItemWidget(item, listItemWidget);
//
//    qDebug() << "Lista utenti dopo l'aggiunta di" << nickname << ":";
//    for (int i = 0; i < count(); ++i) {
//        if (this->item(i)) {
//            qDebug() << "Elemento" << i << ":" << this->item(i)->text();
//        } else {
//            qDebug() << "Elemento" << i << ": null";
//        }
//    }
}

void SortedListWidget::removeItem(const QString &nickname)
{
    for (int i = 0; i < this->count(); ++i)
    {
        QListWidgetItem *item = this->item(i);

        QTextBrowser *textBrowser = qobject_cast<QTextBrowser *>(this->itemWidget(item));

        if (textBrowser && textBrowser->toPlainText() == nickname)
        {
            this->takeItem(i);

            delete item;
            break;
        }
    }
    sortList();
}

void SortedListWidget::sortList()
{
    this->sortItems(Qt::AscendingOrder);
}