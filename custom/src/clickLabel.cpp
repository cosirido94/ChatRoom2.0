#include "../include/clickLabel.h"

ClickLabel::ClickLabel( QWidget *parent)
    : QLabel(parent)
{
    setMouseTracking(true);
}

void ClickLabel::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    QLabel::enterEvent(event);
}

void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QLabel::mousePressEvent(event);
}

void ClickLabel::setText(const QString &text)
{
    QLabel::setText(text);
}