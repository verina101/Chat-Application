#include "MyConstants.h"
#include "ui_ChatRoom.h"
#include "ChatRoom.h"

using namespace std;

ChatRoom::ChatRoom(QWidget *parent): QWidget(parent), ui(new Ui::ChatRoom) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    QPixmap myBackGround("images/Chat_BackGround.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);



    // *************************************** //


    ui->stackedWidget->insertWidget(1,&myChatInfo);
    ui->listWidget->scrollToBottom();

    //openChatRoom();
}

void ChatRoom::openChatRoom() {
    QPixmap piximg(":/images/assets/group_image.png");
    int w = ui->label_image->width();
    int h = ui->label_image->height();


    ui->label_ChatName->setText(MyConstants().getMyChatRoomName());

//   numberOfParticipate = db.SelectData("CHATROOMINFO","NumberOfParticipants","WHERE ChatRoomID = "+ db.convertToValue(MyConstants::getMyChatRoomID())).front().front();

    //----(Messsages)-----//

    string column = "Text, MessageID, SenderName, SenderID, IsDeleted";
    string condition = "WHERE ChatRoomID = " + db.convertToValue(MyConstants::getMyChatRoomID());
    myChatMsgs = db.SelectData("MESSAGE", column, condition);

    for(auto curMsg : myChatMsgs) {
        QString curSenderPic = db.SelectData("USER", "ProfilePicture", "WHERE UserID = " + db.convertToValue(curMsg[3])).front().front();
        DisplayMessage(curMsg[0], curMsg[2], curMsg[3], curSenderPic, 0);
    }
    updateSeen();


}

void ChatRoom::updateSeen(){

    QString myLastSeen = db.SelectData("PARTICIPATE","DateTime","WHERE ChatRoomID = " + db.convertToValue(MyConstants::getMyChatRoomID())+ " AND UserID = " + db.convertToValue(MyConstants::getMyId())).front().front();

    for(auto curMsg : myChatMsgs) {
        db.UpdateData("MESSAGESTATUS","NumberOfViewers = NumberOfViewers + 1 ", "WHERE MessageID =  " + db.convertToValue(curMsg[1]) + " AND DateTime > " + db.convertToValue(myLastSeen));
    }

    db.UpdateData("PARTICIPATE", "DateTime = datetime('now', 'localtime')", "WHERE UserID = " + db.convertToValue(MyConstants::getMyId()));
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

    DisplayMessages();
}

void ChatRoom::DisplayMessages() {

}

void ChatRoom::on_pushButton_send_clicked() {

    QString myMsgText = ui->plainTextEdit->toPlainText();

    DisplayMessage(myMsgText, "", MyConstants::getMyId(), "", 0);

    ui->plainTextEdit->setPlainText("");

    //---------(add Message to database)---------//
    if(myMsgText == "" )
        return;

    db.InsertData("MESSAGE", "( " + db.convertToValue(MyConstants::getMyId()) + " , " + db.convertToValue(MyConstants::getMyChatRoomID()) + " , " + db.convertToValue(MyConstants::getMyName()) + " , " + db.convertToValue(myMsgText) +" , '0' ) ");
    qDebug() << MyConstants::getMyId() + "  " + MyConstants::getMyChatRoomID() + "  " + MyConstants::getMyChatRoomName() + "  " + MyConstants::getMyName() ;
    vector<QString> msgData = db.SelectData("MESSAGE","Text, MessageID, SenderName, SenderID, IsDeleted "," ORDER BY MessageID DESC").front();
    db.InsertData("MESSAGESTATUS","(" + db.convertToValue(msgData[1]) + ", datetime('now','localtime'), '0', '0')");
    myChatMsgs.push_back(msgData);
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


void ChatRoom::on_listWidget_currentRowChanged(int currentRow)
{
    qDebug () <<myChatMsgs[currentRow][1];
    MyConstants::setMyMsgID(myChatMsgs[currentRow][1]);
}



