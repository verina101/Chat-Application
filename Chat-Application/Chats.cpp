#include "ChatItem.h"
#include "Chats.h"
#include "Data.h"
#include "MyConstants.h"
#include "ui_Chats.h"

using namespace std;

Chats::Chats(QWidget *parent): QWidget(parent), ui(new Ui::Chats) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));


    displayChatList();

}

Chats::~Chats() {
    delete ui;
}

void Chats::on_pushButton_createChat_clicked() {

}

void Chats::displayChatList() {
    string table = "PARTICIPATE", columns = "ChatRoomID", cond = "WHERE UserID = '" + MyConstants().myId.toStdString() + "' ORDER BY DateTime Desc";
    vector<vector<QString>> roomsID = db.SelectData(table, columns, cond);
    vector<vector<QString>> msgs = db.SelectData("MESSAGE", "ChatRoomID, SenderName, Text", "ORDER BY MessageID Desc");
    map<QString, int> rooms;
    for(auto it : roomsID) {
        rooms[it[0]] = -1;
    }

    QString chatName;
    for(auto currentMsg : msgs) {
        if(rooms[currentMsg[0] ] == -1) {
            rooms[currentMsg[0]] = 1;

            chatName = db.SelectData("CHATROOM", "Name", "WHERE RoomID = '" + currentMsg[0].toStdString() + "'").front().front();

            myChatsInfo.push_back({currentMsg[0],chatName});

            ChatItem *chatItem = new ChatItem();
            chatItem->setChatData("D:\\downloadss\\633262.png",chatName,currentMsg[1],currentMsg[2]);

            int w = chatItem->width();
            int h = chatItem->height();
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            item->setSizeHint(QSize(w, h));

            ui->listWidget->setItemWidget(item, chatItem);
        }
    }
    for(auto left : rooms) {
        if(left.second == -1) {
            chatName = db.SelectData("CHATROOM", "Name", "WHERE RoomID = '" + left.first.toStdString() + "'").front().front();

            myChatsInfo.push_back({left.first,chatName});

            ChatItem *chatItem = new ChatItem();
            chatItem->setChatData("D:\\downloadss\\633262.png",chatName,"","");

            int w = chatItem->width();
            int h = chatItem->height();
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            item->setSizeHint(QSize(w, h));

            ui->listWidget->setItemWidget(item, chatItem);
        }
    }

}


void Chats::on_listWidget_currentRowChanged(int currentRow)
{
    MyConstants::myChatRoomID = myChatsInfo[currentRow].first;
    MyConstants::myChatRoomName = myChatsInfo[currentRow].second;

//    qDebug () <<MyConstants::myChatRoomID ;
//    qDebug () << MyConstants::myChatRoomName;

}


void Chats::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug () <<MyConstants::myChatRoomID ;
    qDebug () << MyConstants::myChatRoomName;
    hide();
    myChatRoom = new ChatRoom();
    myChatRoom->show();

}

