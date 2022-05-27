#include "showstories.h"
#include "ui_showstories.h"

ShowStories::ShowStories(QWidget *parent): QWidget(parent), ui(new Ui::ShowStories) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    //background
    QPixmap myBackGround("background2.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);


}

ShowStories::~ShowStories() {
    delete ui;
}
