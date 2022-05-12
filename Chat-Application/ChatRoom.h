#ifndef CHATROOM_H
#define CHATROOM_H

#include "ChatInfo.h"
#include "Message.h"
#include "Data.h"
#include <QWidget>
#include <QPixmap>

namespace Ui {
class ChatRoom;
}

class ChatRoom: public QWidget {
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    void DisplayMessage(QString msgText, QString senderName, QString senderID, QString profilePicture, bool isDeleted);

    ~ChatRoom();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_send_clicked();
    void openChatRoom();

signals:
    void exitChat();

private:
    Data db;
    Ui::ChatRoom *ui;
    ChatInfo myChatInfo;
    vector<vector<QString>> myChatMsgs;
};

#endif // CHATROOM_H
