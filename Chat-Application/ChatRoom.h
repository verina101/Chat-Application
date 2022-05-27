#ifndef CHATROOM_H
#define CHATROOM_H

#include "ChatInfo.h"
#include "Message.h"
#include "Data.h"
#include <QWidget>
#include <QPixmap>
#include <QListWidgetItem>

namespace Ui {
class ChatRoom;
}

class ChatRoom: public QWidget {
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();

    void DisplayMessage(QString &msgText, QString senderName, QString senderID, bool isDeleted);


private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_send_clicked();
    void openChatRoom();
    void updateSeen();
    void showContextMenu(const QPoint&);
    void getMsgInfo();
    void deleteMsg();




signals:
    void exitChat();

private:
    Data db;
    Ui::ChatRoom *ui;
    ChatInfo myChatInfo;
    vector<vector<QString>> myChatMsgs;
    QString numberOfParticipate="";


};

#endif // CHATROOM_H
