#include "Message.h"
#include "ui_Message.h"

Message::Message(QWidget *parent) : QWidget(parent),ui(new Ui::Message) {
    ui->setupUi(this);

    QIcon deleteIcon("images\\delete.png");
    QIcon infoIcon("images\\info.jpg");
    ui->comboBox->addItem(infoIcon,"Chat Info");
    ui->comboBox->addItem(deleteIcon,"Delete");
}

Message::~Message()
{
    delete ui;
}

void Message::setMessageText(QString text,int lineCount)
{
    ui->textEdit->setPlainText(text);


    ui->textEdit->setMinimumHeight(lineCount*24);
    ui->textEdit->setMaximumHeight(lineCount*24);


    setMaximumHeight(ui->textEdit->height()+60);
    setMinimumHeight(ui->textEdit->height()+60);


}

void Message::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){ //Message info
        qDebug() <<"0";
    }else{ //Delete Message
        ui->textEdit->setPlainText("THIS MESSAGE IS DELETED");
        ui->textEdit->setMinimumHeight(48);
        ui->textEdit->setMaximumHeight(48);


        setMaximumHeight(ui->textEdit->height()+60);
        setMinimumHeight(ui->textEdit->height()+60);
        qDebug() <<"1";
    }

}

