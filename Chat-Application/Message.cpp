#include "Message.h"
#include "ui_Message.h"

#include <qplaintextedit.h>


using namespace std;

Message::Message(QWidget *parent) : QWidget(parent), ui(new Ui::Message) {
    ui->setupUi(this);


}

bool Message::setMessage(QString msg, bool SentByMe) {
    QString myStyleSheet = "font-size: 14px;";
    myStyleSheet += "font: " + QString(SentByMe ? "black" : "white") + ";";
    myStyleSheet += "background: " + QString(SentByMe ? "lightgrey" : "steelblue") + ";";
    //ui->horizontalLayout_2->hide();
    ConvertFormat(msg);
    if(msg.isEmpty()) return 1;

    ui->label_msg->setStyleSheet(myStyleSheet);
    ui->label_msg->setText(msg);
    ui->label_msg->adjustSize();
    ui->label_msg->setMinimumWidth(ui->label_msg->width() + 8);
    this->adjustSize();
    return 0;
}

void Message::ConvertFormat(QString &str) {
    QPlainTextEdit *tmpo = new QPlainTextEdit();
    tmpo->setGeometry(0, 0, 570, 80);
    tmpo->setStyleSheet("font-size: 14px;");
    tmpo->show();

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
