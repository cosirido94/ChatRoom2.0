#ifndef CHATROOM_CLICKLABEL_H
#define CHATROOM_CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickLabel : public QLabel
{
    Q_OBJECT

public:
    ClickLabel( QWidget *parent = nullptr);
    void setText(const QString &text);

signals:
    void clicked();

protected:
    void enterEvent( QEvent *event ) override;
    void mousePressEvent( QMouseEvent *event ) override;

};
#endif //CHATROOM_CLICKLABEL_H
