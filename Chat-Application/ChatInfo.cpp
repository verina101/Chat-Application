#include "ChatInfo.h"
#include "ui_ChatInfo.h"

ChatInfo::ChatInfo(QWidget *parent): QWidget(parent), ui(new Ui::ChatInfo) {
    ui->setupUi(this);

    QPixmap piximg("D:\\downloadss\\866285.jpg");
    int w = ui->label_picture->width();
    int h = ui->label_picture->height();
    ui->label_picture->setPixmap(piximg.scaled(w, h, Qt::KeepAspectRatioByExpanding));


    QPixmap myBackGround(":/images/assets/Chat_BackGround.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);

}

void ChatInfo::setChatData(bool myChatType, QString myChatName, QString myDescription_admin, QString picture) {
    ui->label_chatType->setText(myChatType == 0 ? "UserName" : "ChatName" );
    ui->label_chatName->setText(myChatName);
    ui->label_descreption_Admin_Type->setText(myChatType == 0 ? "Description: " : "Admin: ");
    ui->label_Description_Admin->setText(myDescription_admin);

    QPixmap piximg(picture);
    int w = ui->label_picture->width();
    int h = ui->label_picture->height();
    ui->label_picture->setPixmap(piximg.scaled(w, h, Qt::IgnoreAspectRatio));

}

ChatInfo::~ChatInfo() {
    delete ui;

}
