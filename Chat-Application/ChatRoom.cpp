#include "ChatRoom.h"
#include "ui_ChatRoom.h"

ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);

    QPixmap piximg("C:\\Users\\Verina Gad\\Desktop\\Moon Knight.jpg");
    int w = ui->label_image->width();
    int h = ui->label_image->height();

    ui->label_image->setPixmap(piximg.scaled(w, h, Qt::IgnoreAspectRatio));

    //connection between chat info screen and chat Room
    ui->stackedWidget->insertWidget(1,&myChatInfo);


}

ChatRoom::~ChatRoom()
{
    delete ui;
}

void ChatRoom::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){ //Chat
        ui->stackedWidget->setCurrentIndex(0);
    }else if(index == 1){ //Chat info
        ui->stackedWidget->setCurrentIndex(1);
    }else //Exit
         qDebug() <<2<<"\n";

}

