#ifndef CHATS_H
#define CHATS_H

#include "ChatRoom.h"
#include "Data.h"
#include "QMap"
#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class Chats;
}

class Chats : public QWidget {
    Q_OBJECT

public:
    explicit Chats(QWidget *parent = nullptr);
    ~Chats();

private slots:
    void on_pushButton_createChat_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void enterchats();

signals :
    void selectChat();

private:
    Ui::Chats *ui;
    void displayChatList();
    Data db;
    ChatRoom myChatRoom ;
    vector<pair<QString,QString>>myChatsInfo;



};

#endif // CHATS_H
