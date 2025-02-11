#include "../include/userWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

UserWidget::UserWidget(const QString &username, QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(150, 30);
    nicknameLabel = new QLabel(username,this);

    removeButton = new QPushButton(this);
    removeButton->setIcon(QIcon("img/cross-mark"));
    removeButton->setFixedSize(20,20);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // Rimuove i margini

    layout->addWidget(nicknameLabel);
    layout->addWidget(removeButton);
    connect(removeButton , &QPushButton::clicked , this , &UserWidget::removeClicked);
}

void UserWidget::removeClicked()
{

}
