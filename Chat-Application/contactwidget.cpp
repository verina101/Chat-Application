#include "contactwidget.h"
#include "ui_contactwidget.h"
#include <QPixmap>
ContactWidget::ContactWidget(QWidget *parent): QWidget(parent), ui(new Ui::ContactWidget) {
    ui->setupUi(this);

}

void ContactWidget::setContactData(QString pic, QString name, QString id) {
    QPixmap piximg(pic);
    int w = ui->Picture->width();
    int h = ui->Picture->height();
    ui->Picture->setPixmap(piximg.scaled(w, h, Qt ::KeepAspectRatioByExpanding));

    ui->Id->setText(id);
    ui->Name->setText(name);
}

ContactWidget::~ContactWidget()
{
    delete ui;
}
