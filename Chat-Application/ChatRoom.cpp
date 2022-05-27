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

    QPixmap piximg("D:/Memes/shrek.jpg");
    int w = ui->label_image->width();
    int h = ui->label_image->height();

    ui->label_image->setPixmap(piximg.scaled(w, h, Qt::IgnoreAspectRatio));
    ui->label_ChatName->setText(MyConstants::myChatRoomName);

    ui->listWidget->scrollToBottom();

    DisplayMessages();
}

void ChatRoom::DisplayMessages() {

}

void ChatRoom::on_pushButton_send_clicked() {
    QString myMsgText = ui->plainTextEdit->toPlainText();

    Message *myMsg = new Message();
    myMsg->ConvertFormat(myMsgText);
    if(myMsgText.isEmpty()) return;
    myMsg->setUserData("Amir Moris", "D:/Memes/messi.jpg");
    myMsg->setMessage(myMsgText, 1);

    int w = myMsg->width();
    int h = myMsg->height();
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(QSize(w, h));
    ui->listWidget->setItemWidget(item, myMsg);
    ui->listWidget->scrollToBottom();
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
    }
}

ChatRoom::~ChatRoom() {
    delete ui;
}
