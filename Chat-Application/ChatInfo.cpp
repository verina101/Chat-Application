#include "ChatInfo.h"
#include "ui_ChatInfo.h"

ChatInfo::ChatInfo(QWidget *parent): QWidget(parent), ui(new Ui::ChatInfo) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));



    QPixmap myBackGround(":/images/assets/Chat_BackGround.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);
}

void ChatInfo::setChatData() {

    ui->listWidget->clear();

    vector<QString> myChatRoomInfo = db.SelectData("CHATROOMINFO", "AdminName, RoomType","WHERE ChatRoomID = "+ db.convertToValue(MyConstants::getMyChatRoomID())).front();
    string cond = "WHERE ChatRoomID = "+ db.convertToValue(MyConstants::getMyChatRoomID()) + " AND UserID !=" +  db.convertToValue(MyConstants::getMyId()) + "ORDER BY DateTime DESC";
    vector<vector<QString>> users = db.SelectData("PARTICIPATE","UserID, DateTime", cond);

    if(myChatRoomInfo[1] == "0"){

        vector<QString> userData= db.SelectData("USER","Description, ProfilePicture","WHERE UserID = " + db.convertToValue(users[0][0])).front();
        ui->label_chatType->setText("UserName: ");
        ui->label_chatName->setText(MyConstants::getMyChatRoomName());
        ui->label_descreption_Admin_Type->setText("Description: ");
        ui->label_Description_Admin->setText(userData[0]);
        ui->label_ListType->setText("Comman Chat Rooms");

        QPixmap piximg(userData[1]);
        int w = ui->label_picture->width();
        int h = ui->label_picture->height();
        ui->label_picture->setPixmap(piximg.scaled(w, h, Qt::IgnoreAspectRatio));

        vector<vector<QString>> myChats = db.SelectData("PARTICIPATE","ChatRoomID", "WHERE UserID = " + db.convertToValue(MyConstants::getMyId()));
        vector<vector<QString>> userChats = db.SelectData("PARTICIPATE","ChatRoomID", "WHERE UserID = " + db.convertToValue(users[0][0]));

        map<QString, bool> mp;
        QString commonRoomID;
        for(auto it : myChats) {
            if(it[0] != MyConstants::getMyChatRoomID())
            mp[it[0]] = 1;
        }

        for(auto it : userChats) {
            if(mp[it[0]]) {
                commonRoomID += "'" + it[0] + "' ,";
            }
        }

        if(!commonRoomID.isEmpty()) {
            commonRoomID.back() = ')';
            commonRoomID = "(" + commonRoomID;

            vector<vector<QString>> coomonChats = db.SelectData("CHATROOM", "Name", "WHERE RoomID in " + commonRoomID.toStdString());
            for(auto it : coomonChats) {
                ui->listWidget->addItem("Chat Name: " + it[0]);
            }
        }

    }
    else {
        ui->label_chatType->setText("ChatName: " );
        ui->label_chatName->setText(MyConstants::getMyChatRoomName());
        ui->label_descreption_Admin_Type->setText("Admin: " );
        ui->label_Description_Admin->setText(myChatRoomInfo[0]);
        ui->label_ListType->setText("Group Participates");

        QPixmap piximg(":/images/assets/group_image.png");
        int w = ui->label_picture->width();
        int h = ui->label_picture->height();
        ui->label_picture->setPixmap(piximg.scaled(w, h, Qt::KeepAspectRatio));

        for(auto user : users) {
            vector<QString> name = db.SelectData("USER","FirstName, LastName","WHERE UserID = " + db.convertToValue(user[0])).front();
            QString userInfo = name[0] + " " + name[1] + "\nLastSeen: " + user[1];
            ui->listWidget->addItem(userInfo);
        }
    }

}

ChatInfo::~ChatInfo() {
    delete ui;
}
