#include "ChatInfo.h"
#include "ui_ChatInfo.h"

ChatInfo::ChatInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatInfo)
{
    ui->setupUi(this);
}

ChatInfo::~ChatInfo()
{
    delete ui;
}
