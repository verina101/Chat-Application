#include "StoryWidget.h"
#include "ui_StoryWidget.h"
#include <iostream>
#include <string>
using namespace std;
StoryWidget::StoryWidget(QWidget *parent):  QWidget(parent), ui(new Ui::StoryWidget) {
    ui->setupUi(this);

}

void StoryWidget::setStoryData(QString name, QString id, QString date) {
    ui->Label_Name->setText(name);
    ui->Label_Id->setText(id);
    if(date.back() == '\n') {
        string tmp = date.toStdString();
        tmp.pop_back();
        date = QString::fromStdString(tmp);
    }
    ui->Label_StoryTime->setText(date);
}

StoryWidget::~StoryWidget() {
    delete ui;
}
