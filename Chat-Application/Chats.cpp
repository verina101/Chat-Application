#include "ChatItem.h"
#include "Chats.h"
#include "Data.h"
#include "ui_Chats.h"
#include "MyConstants.h"

using namespace std;

Chats::Chats(QWidget *parent): QWidget(parent), ui(new Ui::Chats) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));



    ui->stackedWidget->insertWidget(1, &myChatRoom);
    connect(&myChatRoom, SIGNAL(exitChat()), this, SLOT(enterchats()));
    connect(this, SIGNAL(selectChat()), &myChatRoom, SLOT(openChatRoom()));
    displayChatList();

}

Chats::~Chats() {
    delete ui;
}

void Chats::on_pushButton_createChat_clicked() {

}

void Chats::displayChatList() {
    myChatsInfo.clear();

    string table = "PARTICIPATE", columns = "ChatRoomID", cond = "WHERE UserID = " + db.convertToValue(MyConstants::getMyId()) + " ORDER BY DateTime Desc";
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

            chatName = db.SelectData("CHATROOM", "Name", "WHERE RoomID = " + db.convertToValue(currentMsg[0])).front().front();

            myChatsInfo.push_back({currentMsg[0],chatName});

            ChatItem *chatItem = new ChatItem();

            chatItem->setChatData(":/images/assets/ChatRooms_BackGround.jpg",chatName,currentMsg[1],currentMsg[2]);

            int w = chatItem->width();
            int h = chatItem->height();
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            item->setSizeHint(QSize(w, h));
            ui->listWidget->setItemWidget(item, chatItem);
        }
    }
    for(auto left : rooms) {
        if(left.second == -1) {
            chatName = db.SelectData("CHATROOM", "Name", "WHERE RoomID = " + db.convertToValue(left.first)).front().front();

            myChatsInfo.push_back({left.first,chatName});

            ChatItem *chatItem = new ChatItem();
            chatItem->setChatData(":/images/assets/ChatRooms_BackGround.jpg",chatName,"","");

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
    MyConstants::setMyChatRoomID( myChatsInfo[currentRow].first);
    MyConstants::setMyChatRoomName(  myChatsInfo[currentRow].second);

}


void Chats::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    emit selectChat();

    ui->stackedWidget->setCurrentIndex(1);

    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

}

void Chats::enterchats() {
    ui->stackedWidget->setCurrentIndex(0);
    displayChatList();


}

