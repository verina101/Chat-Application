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
    void DisplayMessage(QString &msgText, QString senderName, QString senderID, bool isDeleted);

    map<QString, QString> emoji;

    ~ChatRoom();

private slots:
    void setEmoji(QString representation, QString _emoji);
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_send_clicked();
    void openChatRoom();
    void updateSeen();
    void showContextMenu(const QPoint&);
    void getMsgInfo();
    void deleteMsg();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

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
