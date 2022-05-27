#include "ChatInfo.h"
#include "ui_ChatInfo.h"

ChatInfo::ChatInfo(QWidget *parent): QWidget(parent), ui(new Ui::ChatInfo) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));


}

ChatInfo::~ChatInfo() {
    delete ui;
}
