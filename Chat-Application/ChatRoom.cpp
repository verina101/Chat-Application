#include "ChatRoom.h"
#include "ui_ChatRoom.h"

ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);

    QPixmap piximg("images\\Moon Knight.jpg");
    int w = ui->label_image->width();
    int h = ui->label_image->height();
    ui->label_image->setPixmap(piximg.scaled(w, h, Qt::IgnoreAspectRatio));

    //connection between chat info screen and chat Room
    ui->stackedWidget->insertWidget(1,&myChatInfo);

    ui->listWidget->scrollToBottom();
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


void ChatRoom::on_pushButton_send_clicked()
{
    int lineCount = ui->plainTextEdit_Message->document()->documentLayout()->documentSize().height();
    qDebug()<<lineCount;

    string myText = ui->plainTextEdit_Message->toPlainText().toStdString();
    ui->plainTextEdit_Message->setPlainText(" ");

    //create Message object
    Message *msg = new Message();
    msg->setMessageText(QString::fromStdString(myText),lineCount);

    //create item in list widget
    QListWidgetItem* item= new QListWidgetItem(ui->listWidget);

    //set item size
    int w = msg->width();
    int h = msg->height();
    item->setSizeHint(QSize(w,h));

    ui->listWidget->setItemWidget(item, msg);
    ui->listWidget->scrollToBottom();

}

