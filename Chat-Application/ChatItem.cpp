#include "ChatItem.h"
#include "ui_ChatItem.h"

ChatItem::ChatItem(QWidget *parent): QWidget(parent), ui(new Ui::ChatItem) {
    ui->setupUi(this);



}

ChatItem::~ChatItem() {
    delete ui;
}

void ChatItem::setChatData(QString chatPhoto, QString chatName, QString msgSender, QString msg)
{
    QPixmap piximg(chatPhoto);
    int w = ui->label_chatPhoto->width();
    int h = ui->label_chatPhoto->height();
    ui->label_chatPhoto->setPixmap(piximg.scaled(w, h, Qt::IgnoreAspectRatio));

    ui->label_chatName->setText(chatName);
    QString sender_msg = msg == "" ? "" :  msgSender+" : "+msg;
    ui->label_msgSender->setText(sender_msg);

}
