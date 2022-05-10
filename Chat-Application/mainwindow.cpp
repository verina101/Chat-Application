#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contact.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));


}

MainWindow::~MainWindow() {
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{


    Data MyDataBase;
   // MyDataBase.s.push('w');
    contact *c= new contact();

    //c = new contact(this);
    //c->show();
    //MainWindow().close();
    c->show();

    hide();
}


void MainWindow::on_pushButton_2_clicked()
{
  //  MyDataBase.s.push('w');

//    contact *c= new contact();

//    //c = new contact(this);
//    //c->show();
//    //MainWindow().close();

//    hide();

}

