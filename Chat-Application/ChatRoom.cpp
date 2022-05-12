#include "MyConstants.h"
#include "ui_ChatRoom.h"
#include "ChatRoom.h"
#include "Chats.h"
#include <iostream>
using namespace std;

ChatRoom::ChatRoom(QWidget *parent): QWidget(parent), ui(new Ui::ChatRoom) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));


    QPixmap myBackGround(":/images/assets/Chat_BackGround.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);

    QPixmap myButton(":/icons/assets/Send_Icon.png");
    QIcon iconSendButton (myButton);
    ui->pushButton_send->setIcon(iconSendButton);



    // *************************************** //

    ui->stackedWidget->insertWidget(1,&myChatInfo);
    ui->listWidget->scrollToBottom();

   openChatRoom();
}

void ChatRoom::DisplayMessage(QString msgText, QString senderName, QString senderID, QString profilePicture, bool isDeleted) {

    Message *myMsg = new Message();
    myMsg->ConvertFormat(msgText);
    if(msgText.isEmpty()) return;
    myMsg->setUserData(senderName, profilePicture);
    myMsg->setMessage(msgText, (senderID == MyConstants::getMyId()));

    int w = myMsg->width();
    int h = myMsg->height();
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(QSize(w, h));
    ui->listWidget->setItemWidget(item, myMsg);

    ui->listWidget->scrollToBottom();

}

void ChatRoom::on_pushButton_send_clicked() {
    QString myMsgText = ui->plainTextEdit->toPlainText();
    DisplayMessage(myMsgText, "", MyConstants::getMyId(), "", 0);

    ui->plainTextEdit->setPlainText("");

    //---------(add Message to database)---------//

    //db.InsertData("MESSAGE", "(" + db.convertToValue(MyConstants::getMyId()) + "," + db.convertToValue(MyConstants::getMyChatRoomID()) + "," + db.convertToValue(MyConstants::getMyName()) + "," + db.convertToValue(myMsgText) +",'0')");
    //QString msgID = db.SelectData("MESSAGE","MessageID"," ORDER BY MessageID DESC").front().front();
    //db.InsertData("MESSAGESTATUS","(" + db.convertToValue(msgID) + ", datetime('now'), '0', '0')");
}

void ChatRoom::openChatRoom() {
    ui->label_ChatName->setText(MyConstants().getMyChatRoomName());

    //----(Messsages)-----//

    string column = "Text, MessageID, SenderName, SenderID, IsDeleted";
    string condition = "WHERE ChatRoomID = " + db.convertToValue(MyConstants::getMyChatRoomID());
    myChatMsgs = db.SelectData("MESSAGE", column, condition);

    for(auto curMsg : myChatMsgs) {
        QString curSenderPic = db.SelectData("USER", "ProfilePicture", "WHERE UserID = " + db.convertToValue(curMsg[3])).front().front();
        DisplayMessage(curMsg[0], curMsg[2], curMsg[3], curSenderPic, 0);
    }
}

void ChatRoom::on_comboBox_currentIndexChanged(int index) {
    if(index == 0) { //Chat
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(index == 1) { //Chat info
        ui->stackedWidget->setCurrentIndex(1);
    }
    else { //Exit
        emit exitChat();
        ui->comboBox->setCurrentIndex(0);

        ui->listWidget->blockSignals(true);
        ui->listWidget->clear();
        ui->listWidget->blockSignals(false);
    }
}

ChatRoom::~ChatRoom() {
    delete ui;
}
