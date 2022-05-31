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
    ui->plainTextEdit->clear();
    QPixmap piximg(MyConstants::getMyChatRoomPic());
    int w = ui->label_image->width();
    int h = ui->label_image->height();
    ui->label_image->setPixmap(piximg.scaled(w, h, Qt::KeepAspectRatio));

    ui->label_ChatName->setText(MyConstants().getMyChatRoomName());
    //----(Messsages)-----//

    string column = "Text, MessageID, SenderName, SenderID, IsDeleted";
    string condition = "WHERE ChatRoomID = " + db.convertToValue(MyConstants::getMyChatRoomID());
    myChatMsgs = db.SelectData("MESSAGE", column, condition);
    QString s = db.SelectData("CHATROOMINFO", "RoomType", condition).front().front();
    isGroupChat = s.toInt();
    for(auto curMsg : myChatMsgs) {
        DisplayMessage(curMsg[0], curMsg[2], curMsg[3], curMsg[4] == '1', 0);
    }
    updateSeen();
}

void ChatRoom::updateSeen(){
    QString myLastSeen = db.SelectData("PARTICIPATE","DateTime","WHERE ChatRoomID = " + db.convertToValue(MyConstants::getMyChatRoomID())+ " AND UserID = " + db.convertToValue(MyConstants::getMyId())).front().front();

    for(auto curMsg : myChatMsgs) {
        db.UpdateData("MESSAGESTATUS","NumberOfViewers = NumberOfViewers + 1 ", "WHERE MessageID =  " + db.convertToValue(curMsg[1]) + " AND DateTime > " + db.convertToValue(myLastSeen));
    }

}

void ChatRoom::DisplayMessage(QString &msgText, QString senderName, QString senderID, bool isDeleted, bool isNew) {
    if(msgText.isEmpty()) return;
    Message *myMsg = new Message();
    if(isNew) myMsg->ConvertFormat(msgText);

    if(isDeleted) {
        if(MyConstants::getMyId() == senderID)
            myMsg->setMessage("YOU DELETED THIS MESSAGE", 1, isGroupChat);
        else
            myMsg->setMessage("THIS MESSAGE WAS DELETED", 0, isGroupChat);
    }
    else {
        myMsg->setMessage(msgText, (senderID == MyConstants::getMyId()), isGroupChat);
    }

    if(senderID != MyConstants::getMyId() && userColorIndex.find(senderID) == userColorIndex.end()) {
        int getRandomColor = getRandomNumber(myMsg->getColorsCount());
        userColorIndex[senderID] = getRandomColor;
        isUsed[getRandomColor] = 1;
    }
    myMsg->setUserData(senderName, userColorIndex[senderID]);
    int w = myMsg->width();
    int h = myMsg->height();
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(QSize(w, h));

    ui->listWidget->setItemWidget(item, myMsg);
    ui->listWidget->scrollToBottom();

}

int ChatRoom::getRandomNumber(int total) {
    if((int)isUsed.size() == total) isUsed.clear();
    int randomColor = rand() % total;
    if(isUsed.find(randomColor) != isUsed.end()) return randomColor = getRandomNumber(total);
    return randomColor;
}

void ChatRoom::on_pushButton_send_clicked() {
    QString myMsgText = ui->plainTextEdit->toPlainText();
    DisplayMessage(myMsgText, "", MyConstants::getMyId(), 0,1);

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
    msg->setMessage("YOU DELETED THIS MESSAGE", 1, isGroupChat);
    ui->listWidget->setItemWidget(item,msg);
}


void ChatRoom::on_pushButton_1_clicked() {
    QString myEmoji = ui->pushButton_1->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_2_clicked()
{

    QString myEmoji = ui->pushButton_2->text();
    ui->plainTextEdit->insertPlainText(myEmoji);

}


void ChatRoom::on_pushButton_3_clicked()
{
    QString myEmoji = ui->pushButton_3->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_4_clicked()
{
    QString myEmoji = ui->pushButton_4->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_5_clicked()
{
    QString myEmoji = ui->pushButton_5->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_6_clicked()
{
    QString myEmoji = ui->pushButton_6->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_7_clicked()
{
    QString myEmoji = ui->pushButton_7->text();
    ui->plainTextEdit->insertPlainText(myEmoji);

}


void ChatRoom::on_pushButton_8_clicked()
{
    QString myEmoji = ui->pushButton_8->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_9_clicked()
{
    QString myEmoji = ui->pushButton_9->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_10_clicked()
{
    QString myEmoji = ui->pushButton_10->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}


void ChatRoom::on_pushButton_11_clicked()
{
    QString myEmoji = ui->pushButton_11->text();
    ui->plainTextEdit->insertPlainText(myEmoji);
}

