#include "../include/sortedListWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include "../include/clickLabel.h"

SortedListWidget::SortedListWidget(QWidget *parent) : QListWidget(parent)
{
//    this->setSortingEnabled(true);
//    sortList();
    setSelectionMode(QAbstractItemView::NoSelection);
    // Stile CSS per migliorare l'aspetto della lista
    setStyleSheet("QListWidget {"
                  "background-color: #f9f9f9;"
                  "border: none;"
                  "padding: 5px;"
                  "}"
                  "QListWidget::item {"
                  "border: none;"
                  "}");
}

void SortedListWidget::addItem(const QString &nickname, const QString &color)
{
    QWidget* listItemWidget = createListItemWidget(nickname,color);

    QListWidgetItem* item = createListWidgetItem(nickname);
    insertItemSorted(item);
    setItemWidget(item,listItemWidget);
//    // Creazione del widget personalizzato per l'elemento della lista
//    QWidget *listItemWidget = new QWidget();
//    QHBoxLayout *layout = new QHBoxLayout(listItemWidget);
//
//    // Creazione dell'icona del messaggio
//    QIcon messageIcon("img/message-icon.png");
//    QLabel *iconLabel = new QLabel();
//    iconLabel->setPixmap(messageIcon.pixmap(QSize(20, 20)));
//
//    // Creazione del testo formattato per il nome utente
//    QString coloredNickname = QString("<font color='%1'>%2</font>").arg(color, nickname);
//    QLabel *nicknameLabel = new QLabel(coloredNickname);
//
//    // Aggiunta dell'icona e del nome utente al layout
//    layout->addWidget(nicknameLabel);
//    layout->addSpacing(5); // Spazio tra l'icona e il nome utente
//    layout->addWidget(iconLabel);
//
//    // Imposta il layout e i margini
//    layout->setContentsMargins(0, 0, 0, 0);
//
//    // Crea un nuovo elemento della lista
//    QListWidgetItem *item = new QListWidgetItem();
//    item->setData(Qt::UserRole, nickname); // Salva il nickname come dati dell'elemento
//    item->setSizeHint(QSize(120, 25)); // Dimensione personalizzabile
//
//    // Inserisce l'elemento nella lista in modo ordinato
//    int index = 0;
//    while (index < count() && this->item(index)->data(Qt::UserRole).toString() < nickname) {
//        ++index;
//    }
//    insertItem(index, item);
//    setItemWidget(item, listItemWidget);
}

void SortedListWidget::removeItem(const QString &nickname)
{
    for(int i = 0; i < count(); ++i)
    {
        QListWidgetItem *item = this->item(i);

        if(item)
        {
            QString currentNickname = item->data(Qt::UserRole).toString();

            if( currentNickname == nickname)
            {
                delete takeItem(i);
                break;
            }
        }
    }
}

void SortedListWidget::insertItemSorted(QListWidgetItem *item)
{
    int index = 0;
    QString itemNickname = item->data(Qt::UserRole).toString();

    while(index < count() && this->item(index)->data(Qt::UserRole).toString() < itemNickname )
    {
        QString currentNickname = this->item(index)->data(Qt::UserRole).toString();

        if( currentNickname < itemNickname )
        {
            ++index;
        }
        else
        {
            break;
        }
    }
    insertItem(index,item);
}

QListWidgetItem* SortedListWidget::createListWidgetItem(const QString &nickname)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole,nickname);
    item->setSizeHint(QSize(120,35));

    item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);

    return item;
}

QWidget* SortedListWidget::createListItemWidget(const QString &nickname, const QString &color)
{
    QWidget *widget = new QWidget();
    widget->setStyleSheet("border: none;");
//    widget->setFixedSize(120,25);
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(8); // Spaziatura tra nickname e icona

    QLabel *nicknameLabel = createNicknameLabel(nickname,color);
//    layout->addStretch();
    QLabel *iconLabel = createIconLabel(nickname);

//    qDebug() << "Size nicknameLabel " << nicknameLabel->size();
//    qDebug() << "Size iconLabel" << iconLabel->size();
//    qDebug() << "Size widget" << widget->size();
//    qDebug() << "this" << this->size();
    layout->addWidget(nicknameLabel);

    // Aggiungi uno spaziatore per creare uno spazio tra il nome utente e l'icona

    layout->addStretch();
    layout->addWidget(iconLabel);
//    layout->setContentsMargins(0,0,0,0);
    widget->setFixedHeight(30);
    return widget;
}

QLabel* SortedListWidget::createNicknameLabel(const QString &nickname, const QString &color)
{
    QString styledNickname = QString("<font color='%1'style='font-size:18px;'>%2</font>").arg(color,nickname);
    QLabel *label = new QLabel(styledNickname);
//    label->setFixedSize(100,20);
    // Imposta QSizePolicy per rendere flessibile il ridimensionamento
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    label->setFixedHeight(20);  // Altezza fissa per il nickname label
    label->setContentsMargins(0, 0, 0, 0);
    return label;
}

QLabel* SortedListWidget::createIconLabel(const QString& nickname)
{
    QIcon messageIcon("img/message-icon.png");
    QPixmap pixmap = messageIcon.pixmap(QSize(20,20));
    ClickLabel *label = new ClickLabel();
    label->setFixedSize(20, 20);
    label->setPixmap(pixmap);

    connect(label, &ClickLabel::clicked , this , [this,nickname]()
    {
        emit messageIconClicked(nickname);
    });

    return label;
}

QString SortedListWidget::getNickname(int index) const
{
    if (index < 0 || index >=count() )
    {
        return QString();
    }
    else
    {
        QListWidgetItem* item = this->item(index);
        return item->data(Qt::UserRole).toString();
    }
}
