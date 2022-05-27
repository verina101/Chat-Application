#include "ui_Message.h"
#include "Message.h"


using namespace std;

Message::Message(QWidget *parent) : QWidget(parent), ui(new Ui::Message) {
    ui->setupUi(this);

    QIcon iconInfo(":/icons/assets/Info_Icon.png");
    QIcon iconDelete(":/icons/assets/Delete_Icon.png");
    ui->comboBox->setItemIcon(0, iconInfo);
    ui->comboBox->setItemIcon(1, iconDelete);

}

void Message::setUserData(QString userName, QString userPhoto) {
    ui->label_Sender_Name->setText(userName);

    QPixmap piximg(userPhoto);
    int w = ui->label_Sender_Image->width();
    int h = ui->label_Sender_Image->height();
    ui->label_Sender_Image->setPixmap(piximg.scaled(w, h, Qt::IgnoreAspectRatio));
}

void Message::setMessage(QString msg, bool SentByMe) {
    QString myStyleSheet = "font-size: 14px; border-radius:15px; margin-left: 1;";
    myStyleSheet += "font: " + QString(SentByMe ? "black" : "white") + ";";
    myStyleSheet += "background: " + QString(SentByMe ? "lightgrey" : "steelblue") + ";";

    if(SentByMe) {
        ui->label_Sender_Image->hide();
        ui->label_Sender_Name->hide();
        myStyleSheet += "font: black; background: lightgrey;";
        ui->widget->setMaximumHeight(20);
    }
    else {
        ui->comboBox->removeItem(1);
        myStyleSheet += "font: white; background: steelblue;";
        ui->horizontalLayout_2->setDirection(QBoxLayout::RightToLeft);
    }

    ui->label_msg->setStyleSheet(myStyleSheet);
    ui->label_msg->setText(msg);
    ui->label_msg->adjustSize();
    ui->label_msg->setMinimumWidth(ui->label_msg->width() + 8);
    ui->label_msg->setMaximumHeight(ui->label_msg->height());
    this->adjustSize();
}

void Message::ConvertFormat(QString &str) {
    QPlainTextEdit *tmpo = new QPlainTextEdit();
    tmpo->setGeometry(0, 0, 570, 80);
    tmpo->setStyleSheet("font-size: 14px;");
    tmpo->show();
    tmpo->hide();

    string tmpStr = str.toStdString(), subStr = "";
    tmpo->setPlainText(QString::fromStdString(subStr));
    while(!tmpStr.empty() && (tmpStr.back() == '\n' || tmpStr.back() == ' '))
        tmpStr.pop_back();

    str.clear();
    for(auto ch : tmpStr) {
        subStr += ch;
        int oLd_nLines = tmpo->document()->documentLayout()->documentSize().height();

        tmpo->setPlainText(QString::fromStdString(subStr));
        int new_nLines = tmpo->document()->documentLayout()->documentSize().height();

        string addChar (1, ch);
        if(oLd_nLines != new_nLines && ch != '\n') {
            addChar = '\n' + addChar;
        }
        str += QString::fromStdString(addChar);
    }
    //qDebug() << str;
    tmpo->close();
}

Message::~Message() {
    delete ui;
}



void Message::on_comboBox_activated(int index)
{
    if(index == 0) {
       vector<QString> msgData =  db.SelectData("MESSAGESTATUS"," DateTime, NumberOfViewers ", "WHERE MessageID = " + db.convertToValue(MyConstants::getMyMsgID())).front();
       QString numberOfParticipate = db.SelectData("CHATROOMINFO","NumberOfParticipants","WHERE ChatRoomID = "+ db.convertToValue(MyConstants::getMyChatRoomID())).front().front();
        qDebug() <<numberOfParticipate <<"  "<<msgData[1];
        myMsgStatus = new MsgStatus();
       myMsgStatus->setMsgStatus(msgData[0].left(10),msgData[0].right(9), (numberOfParticipate==msgData[1] ? 1 : 0));
       myMsgStatus->show();
    }
}

