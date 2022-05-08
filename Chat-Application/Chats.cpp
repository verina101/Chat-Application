#include "Chats.h"
#include "Data.h"
#include "MyConstants.h"
#include "ui_Chats.h"

using namespace std;

Chats::Chats(QWidget *parent): QWidget(parent), ui(new Ui::Chats) {
    ui->setupUi(this);

    displayChatList();


}

Chats::~Chats() {
    delete ui;
}

void Chats::on_pushButton_createChat_clicked() {

}

void Chats::displayChatList()
{
    string table = "PARTICIPATE", columns = "ChatRoomID", cond = "WHERE UserID = '" + MyConstants().myId + "' ORDER BY DateTime Desc";
    vector<vector<QString>> roomsID = db.SelectData(table, columns, cond);
    vector<vector<QString>> msgs = db.SelectData("MESSAGE", "ChatRoomID, SenderName, Text", "ORDER BY MessageID Desc");
    map<QString, int> rooms;
    for(auto it : roomsID) {
        rooms[it[0]] = -1;
    }

    QString chatname;
    for(auto currentMsg : msgs) {
        if(rooms[currentMsg[0] ] == -1) {

            rooms[currentMsg[0]] = 1;
            chatname = db.SelectData("CHATROOM", "Name", "WHERE RoomID = '" + currentMsg[0].toStdString() + "'").front().front();
            chatname += "\n" + currentMsg[1] + ":  " + currentMsg[2];
            ui->listWidget->addItem(chatname);
        }
    }
    for(auto left : rooms) {
        if(left.second == -1) {
            chatname = db.SelectData("CHATROOM", "Name", "WHERE RoomID = '" + left.first.toStdString() + "'").front().front();
             ui->listWidget->addItem(chatname);
        }
    }

}

