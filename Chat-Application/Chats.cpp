#include "ChatItem.h"
#include "Chats.h"
#include "Data.h"
#include "ui_Chats.h"
#include "MyConstants.h"
#include "addstory.h"
#include "ShowContactNameStory.h"
#include "contact.h"
#include "showcontact.h"

using namespace std;

Chats::Chats(QWidget *parent): QWidget(parent), ui(new Ui::Chats) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    //chatRoom Connection
    ui->stackedWidget->insertWidget(1, &myChatRoom);
    connect(&myChatRoom, SIGNAL(exitChat()), this, SLOT(enterchats()));
    connect(this, SIGNAL(selectChatRoom()), &myChatRoom, SLOT(openChatRoom()));

    //Show Contact Connection
    ui->stackedWidget->insertWidget(2,&showContact);
    connect(&showContact, SIGNAL(exitShowContact()),this, SLOT(enterchats()));
    connect(this,SIGNAL(selectShowContact()),&showContact,SLOT(openShowContact()));

    //to open chatRoom when click on it in showContact
    connect(&showContact, SIGNAL(openContactChat()),this, SLOT(openChatRoomFromContact()));

    //Add Contact Connection
    ui->stackedWidget->insertWidget(3,&myContact);
    connect(&myContact,SIGNAL(exitAddContact()),this,SLOT(enterchats()));
    connect(this,SIGNAL(selectAddContact()),&myContact,SLOT(openAddContact()));






    displayChatList();



}

Chats::~Chats() {
    delete ui;
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
            chatName = getChatName(chatName);
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
            chatName = getChatName(chatName);
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

QString Chats::getChatName(QString chatName)
{
    int idIndex = 0;
    if(chatName.contains('#')){
        QList myList =  chatName.split('#');
        if(MyConstants::getMyId() == myList[0]){
            idIndex = 1;
        }
        vector<QString> otherUserName = db.SelectData("USER","FirstName, LastName"," WHERE UserID = " + db.convertToValue(myList[idIndex])).front();

        return otherUserName[0] + " " + otherUserName[1];
    }
    return chatName;

}


void Chats::on_listWidget_currentRowChanged(int currentRow)
{
    MyConstants::setMyChatRoomID( myChatsInfo[currentRow].first);
    MyConstants::setMyChatRoomName(  myChatsInfo[currentRow].second);

}


void Chats::on_listWidget_itemDoubleClicked(QListWidgetItem *item){
    emit selectChatRoom();

    ui->stackedWidget->setCurrentIndex(1);

    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

}

void Chats::enterchats() {
    ui->stackedWidget->setCurrentIndex(0);
    displayChatList();


}


void Chats::on_pushButton_addStory_clicked(){
    AddStory *addStory = new AddStory();
    addStory->show();
    this->close();
}


void Chats::on_pushButton_viewStory_clicked(){
    ShowContactNameStory *showContactNameStory = new ShowContactNameStory();
    showContactNameStory->show();
    this->close();
}

//-----(Contact class)-----//
void Chats::on_pushButton_addContact_clicked(){
    emit selectAddContact();


    ui->stackedWidget->setCurrentIndex(3);

    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

}

//-----(Show Contact class)-----//
void Chats::openChatRoomFromContact()
{
    emit selectChatRoom();

    ui->stackedWidget->setCurrentIndex(1);

    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);
}

void Chats::on_pushButton_createChat_clicked() {
    emit selectShowContact();

    ui->stackedWidget->setCurrentIndex(2);

    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

}

