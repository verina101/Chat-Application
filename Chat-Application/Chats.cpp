#include "Chats.h"
#include "Data.h"
#include "MyConstants.h"
#include "ui_Chats.h"

using namespace std;

Chats::Chats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chats)
{
    ui->setupUi(this);


    string table = "PARTICIPATE", columns = "ChatRoomID", cond = "WHERE UserID ='"+MyConstants().myId+"' ORDER BY Time Desc";
    vector<vector<QString>> roomsID = db.SelectData(table,columns,cond);
    for(auto id : roomsID){
        cerr<< "###### \n";
        vector<vector<QString>> roomsName = db.SelectData("CHATROOM","Name","WHERE RoomID ='"+id[0].toStdString()+"'");
        vector<vector<QString>> lastMsg = db.SelectData("MESSAGE","SenderName, Text","WHERE ChatRoomID ='"+id[0].toStdString()+"' and isDeleted = '0'  ORDER BY MessageID Desc");

        QString myString = id[0]+" " +roomsName[0][0];
        if(lastMsg.size()){
            myString += "\n"+lastMsg[0][0] + " : " + lastMsg[0][1];
        }
        ui->listWidget->addItem(myString);

    }
}

Chats::~Chats()
{
    delete ui;
}

void Chats::on_pushButton_createChat_clicked()
{

}

