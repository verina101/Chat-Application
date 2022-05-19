#include "MsgStatus.h"
#include "ui_MsgStatus.h"

MsgStatus::MsgStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgStatus)
{
    ui->setupUi(this);
}

void MsgStatus::setMsgStatus(QString date, QString time, bool isSeen) {
    ui->label_msgTime->setText(time);
    ui->label_msgDate->setText(date);

    QString myIcon;
    if(isSeen)
         myIcon = ":/icons/assets/seen_Icon.png";
    else
         myIcon = ":/icons/assets/notSeen_Icon.png";

    QPixmap myButton(myIcon);
    QIcon iconSendButton (myButton);
    ui->pushButton->setIcon(iconSendButton);

}

MsgStatus::~MsgStatus()
{
    delete ui;
}
