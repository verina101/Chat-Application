#include "MyConstants.h"
#include "qmenu.h"
#include "ui_ChatRoom.h"
#include "ChatRoom.h"
#include "Chats.h"
#include <iostream>
using namespace std;

ChatRoom::ChatRoom(QWidget *parent): QWidget(parent), ui(new Ui::ChatRoom) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    QString myStyleSheet = "background: url(':/images/assets/login_BackGround.png');";
    this->setStyleSheet(myStyleSheet);

    QPixmap myButton(":/icons/assets/Send_Icon.png");
    QIcon iconSendButton (myButton);
    ui->pushButton_send->setIcon(iconSendButton);

    // *************************************** //

    ui->stackedWidget->insertWidget(1,&myChatInfo);
    ui->listWidget->scrollToBottom();

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

}

void ChatRoom::openChatRoom() {
    QPixmap piximg(":/images/assets/group_image.png");
    int w = ui->label_image->width();
    int h = ui->label_image->height();
    ui->label_image->setPixmap(piximg.scaled(w, h, Qt::KeepAspectRatio));

    ui->label_ChatName->setText(MyConstants().getMyChatRoomName());
    //----(Messsages)-----//

    string column = "Text, MessageID, SenderName, SenderID, IsDeleted";
    string condition = "WHERE ChatRoomID = " + db.convertToValue(MyConstants::getMyChatRoomID());
    myChatMsgs = db.SelectData("MESSAGE", column, condition);

    for(auto curMsg : myChatMsgs) {
        DisplayMessage(curMsg[0], curMsg[2], curMsg[3], curMsg[4] == '1');
    }
    updateSeen();
}

void ChatRoom::updateSeen(){
    QString myLastSeen = db.SelectData("PARTICIPATE","DateTime","WHERE ChatRoomID = " + db.convertToValue(MyConstants::getMyChatRoomID())+ " AND UserID = " + db.convertToValue(MyConstants::getMyId())).front().front();

    for(auto curMsg : myChatMsgs) {
        db.UpdateData("MESSAGESTATUS","NumberOfViewers = NumberOfViewers + 1 ", "WHERE MessageID =  " + db.convertToValue(curMsg[1]) + " AND DateTime > " + db.convertToValue(myLastSeen));
    }

}

void ChatRoom::DisplayMessage(QString &msgText, QString senderName, QString senderID, bool isDeleted) {
    Message *myMsg = new Message();
    myMsg->ConvertFormat(msgText);
    if(msgText.isEmpty()) return;

    if(isDeleted) {
        if(MyConstants::getMyId() == senderID)
            myMsg->setMessage("YOU DELETED THIS MESSAGE", 1);
        else
            myMsg->setMessage("THIS MESSAGE WAS DELETED", 0);
    }
    else {
        myMsg->setMessage(msgText, (senderID == MyConstants::getMyId()));
    }
    int color;
    myMsg->setUserData(senderName, color);
    int w = myMsg->width();
    int h = myMsg->height();
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(QSize(w, h));

    ui->listWidget->setItemWidget(item, myMsg);
    ui->listWidget->scrollToBottom();

}

void ChatRoom::on_pushButton_send_clicked() {
    QString myMsgText = ui->plainTextEdit->toPlainText();
    DisplayMessage(myMsgText, "", MyConstants::getMyId(), 0);

    ui->plainTextEdit->setPlainText("");

    //---------(add Message to database)---------//
    if(myMsgText.isEmpty()) return;

    db.InsertData("MESSAGE", "( " + db.convertToValue(MyConstants::getMyId()) + " , " + db.convertToValue(MyConstants::getMyChatRoomID()) + " , " + db.convertToValue(MyConstants::getMyName()) + " , " + db.convertToValue(myMsgText) +" , '0' ) ");
    vector<QString> msgData = db.SelectData("MESSAGE","Text, MessageID, SenderName, SenderID, IsDeleted "," ORDER BY MessageID DESC").front();
    db.InsertData("MESSAGESTATUS","(" + db.convertToValue(msgData[1]) + ", datetime('now','localtime'), '1', '0')");
    db.UpdateData("PARTICIPATE", "DateTime = datetime('now', 'localtime')", "WHERE UserID = " + db.convertToValue(MyConstants::getMyId()));

    myChatMsgs.push_back(msgData);
}



void ChatRoom::on_comboBox_currentIndexChanged(int index) {
    db.UpdateData("PARTICIPATE", "DateTime = datetime('now', 'localtime')", "WHERE UserID = " + db.convertToValue(MyConstants::getMyId()));

    if(index == 0) { //Chat
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(index == 1) { //Chat info
        ui->stackedWidget->setCurrentIndex(1);
        myChatInfo.setChatData();
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

void ChatRoom::showContextMenu(const QPoint &pos){
    int curMsg = ui->listWidget->currentRow();
    if(myChatMsgs[curMsg][4] == '1') return;

    QPoint globalPos = ui->listWidget->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction("Info", this, SLOT(getMsgInfo()));
    if(myChatMsgs[curMsg][3] == MyConstants::getMyId()) {
        myMenu.addAction("Delete",  this, SLOT(deleteMsg()));
    }
    MyConstants::setMyMsgID(myChatMsgs[curMsg][1]);

    myMenu.exec(globalPos);
}

void ChatRoom::getMsgInfo() {
    Message *msg = new Message();
    msg->getMessageInfo(MyConstants::getMyMsgID());

}

void ChatRoom::deleteMsg() {
    Message *msg = new Message();
    msg->deleteMessage(MyConstants::getMyMsgID());
    QListWidgetItem *item = ui->listWidget->currentItem();
    msg->setMessage("YOU DELETED THIS MESSAGE", 1);
    ui->listWidget->setItemWidget(item,msg);
}



