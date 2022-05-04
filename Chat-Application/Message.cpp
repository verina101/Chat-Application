#include "Message.h"
#include "ui_Message.h"

Message::Message(QWidget *parent) : QWidget(parent),ui(new Ui::Message) {
    ui->setupUi(this);


    QIcon x("C:\\Users\\Verina Gad\\Desktop\\download.png");
    ui->comboBox->addItem(x,"Chat Info");
    ui->comboBox->addItem(x,"Delete");
}

Message::~Message()
{
    delete ui;
}
