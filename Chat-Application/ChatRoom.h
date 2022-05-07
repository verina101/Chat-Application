#ifndef CHATROOM_H
#define CHATROOM_H

#include "ChatInfo.h"
#include "Message.h"

#include <QWidget>
#include <QPixmap>

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_send_clicked();

private:
    Ui::ChatRoom *ui;
    ChatInfo myChatInfo;
};

#endif // CHATROOM_H
