#ifndef CHATS_H
#define CHATS_H

#include "ChatRoom.h"
#include "Data.h"
#include "QMap"
#include "contact.h"
#include "showcontact.h"
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
    void on_pushButton_addStory_clicked();
    void on_pushButton_viewStory_clicked();
    void on_pushButton_addContact_clicked();
    void openChatRoomFromContact();
    void on_pushButton_createGroup_clicked();
    void on_pushButton_Profile_clicked();
    void on_pushButton_logOut_clicked();

signals :
    void selectAddContact();
    void selectChatRoom();
    void selectShowContact();

private:
    Ui::Chats *ui;

    Data db;
    ChatRoom myChatRoom ;
    ShowContact showContact ;
    contact myContact;
    vector<pair<QString,pair<QString,QString>>>myChatsInfo;

    void displayChatList();
    pair<QString,QString> getChatInfo(QString chatName);



};

#endif // CHATS_H
