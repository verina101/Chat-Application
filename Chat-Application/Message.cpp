#include "ui_Message.h"
#include "Message.h"
#include "MyConstants.h"
using namespace std;

Message::Message(QWidget *parent) : QWidget(parent), ui(new Ui::Message) {
    ui->setupUi(this);

}

void Message::setUserData(QString userName, int colorIndex) {
    ui->label_Sender_Name->setText(userName);
    ui->label_Sender_Name->setStyleSheet("color: " + colors[colorIndex] + "; font-size: 16px;");

}

int Message::getColorsCount() {
    return colors.size();
}

void Message::setMessage(QString msg, bool SentByMe, bool isGroupChat) {
    QString myStyleSheet = "font-size: 14px; border-radius:15px; margin-left: 1;";
    myStyleSheet += "font: " + QString(SentByMe ? "black" : "white") + ";";
    myStyleSheet += "background: " + QString(SentByMe ? "rgb(18, 140, 126)" : "steelblue") + ";";

    if(SentByMe || !isGroupChat) {
        ui->label_Sender_Name->setMinimumHeight(0);
        ui->label_Sender_Name->setMaximumHeight(0);
        ui->label_Sender_Name->hide();
    }
    if(!SentByMe) {
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
    int l = str.size();
    while(l && (str[l - 1] == '\n' || str[l - 1] == ' ')) {
        l--;
    }

    str = str.left(l);
    QString tmpqStr = str;
    str.clear();
    for(auto ch : tmpqStr) {
        if(ch == '\'')
            ch = '"';
        int oLd_nLines = tmpo->document()->documentLayout()->documentSize().height();
        tmpo->insertPlainText(ch);
        int new_nLines = tmpo->document()->documentLayout()->documentSize().height();

        QString addChar (1, ch);
        if(oLd_nLines != new_nLines && ch != '\n') {
            addChar = '\n' + addChar;
        }
        str += addChar;
    }
    tmpo->close();
}

Message::~Message() {
    delete ui;
}

void Message::getMessageInfo(QString messageID) {
    vector<QString> msgData =  db.SelectData("MESSAGESTATUS"," DateTime, NumberOfViewers ", "WHERE MessageID = " + db.convertToValue(messageID)).front();
    QString numberOfParticipate = db.SelectData("CHATROOMINFO","NumberOfParticipants","WHERE ChatRoomID = "+ db.convertToValue(MyConstants::getMyChatRoomID())).front().front();
    myMsgStatus->setMsgStatus(msgData[0].left(10),msgData[0].right(9), numberOfParticipate==msgData[1]);
    myMsgStatus->exec();
}

void Message::deleteMessage(QString messageID) {
    db.UpdateData("MESSAGE","Text = 'THIS MESSAGE WAS DELETED' , isDeleted = '1'","WHERE MessageID = " + db.convertToValue(messageID) );

}
