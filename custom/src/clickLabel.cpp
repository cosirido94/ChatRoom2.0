#include "../include/clickLabel.h"

ClickLabel::ClickLabel(const QString &text, QWidget *parent)
    : QLabel(text,parent)
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