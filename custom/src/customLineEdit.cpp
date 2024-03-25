#include "include/customLineEdit.h"
#include <iostream>
CustomLineEdit::CustomLineEdit(QWidget *parent) : QLineEdit(parent)
{
    indicatorLabel = new QLabel(this);
    indicatorLabel->setScaledContents(true);
    indicatorLabel->setFixedSize(18,18);
//    indicatorLabel->setPixmap(QPixmap("img/check-mark.png"));
    adjustIndicatorPosition();
//    connect(this, &QLineEdit::textChanged , this , &CustomLineEdit::validateAddress);
    checkMark = false;
}

QLabel* CustomLineEdit::getIndicatorLabel() const
{
    return indicatorLabel;
}

bool CustomLineEdit::getCheckMark()
{
    return checkMark;
}

void CustomLineEdit::setCheckMark(bool x)
{
    checkMark = x;
}
void CustomLineEdit::adjustIndicatorPosition()
{
    indicatorLabel->move(this->width() - indicatorLabel->width() -5, (this->height() - indicatorLabel->height()) / 2);
}

void CustomLineEdit::paintEvent(QPaintEvent* event )
{
    QLineEdit::paintEvent(event);
}

void CustomLineEdit::resizeEvent(QResizeEvent* event) {
    QLineEdit::resizeEvent(event); // Chiamata al resizeEvent della classe base
    adjustIndicatorPosition(); // Aggiorna la posizione dell'indicatore
}


void CustomLineEdit::textChanged(const QString &text)
{
    emit textChanged(text);
}