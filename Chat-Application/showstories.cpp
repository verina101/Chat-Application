#include "showstories.h"
#include "ui_showstories.h"

ShowStories::ShowStories(QWidget *parent): QWidget(parent), ui(new Ui::ShowStories) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));


}

ShowStories::~ShowStories() {
    delete ui;
}
