#include "ChatItem.h"
#include "ui_ChatItem.h"

ChatItem::ChatItem(QWidget *parent): QWidget(parent), ui(new Ui::ChatItem) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));


}

ChatItem::~ChatItem() {
    delete ui;
}
