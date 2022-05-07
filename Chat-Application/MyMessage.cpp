#include "MyMessage.h"
#include "ui_MyMessage.h"

MyMessage::MyMessage(QWidget *parent) : Message(parent), ui(new Ui::MyMessage) {
    ui->setupUi(this);


}

MyMessage::~MyMessage() {
    delete ui;
}
