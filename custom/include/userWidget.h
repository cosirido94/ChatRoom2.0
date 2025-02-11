#ifndef CHATROOM_USERWIDGET_H
#define CHATROOM_USERWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(const QString& username , QWidget* parent = nullptr);

private slots:
    void removeClicked();

private:
    QLabel* nicknameLabel;
    QPushButton* removeButton;
};
#endif //CHATROOM_USERWIDGET_H
