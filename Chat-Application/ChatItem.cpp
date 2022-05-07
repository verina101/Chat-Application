#include "ChatItem.h"
#include "ui_ChatItem.h"

ChatItem::ChatItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatItem)
{
    ui->setupUi(this);
}

ChatItem::~ChatItem()
{
    delete ui;
}
