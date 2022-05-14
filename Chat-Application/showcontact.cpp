#include "showcontact.h"
#include "ui_showcontact.h"
#include "ui_contact.h"
#include <QPixmap>
#include "contact.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include "Data.h"
#include <QMap>


using namespace std;

ShowContact::ShowContact(QWidget *parent): QWidget(parent), ui(new Ui::ShowContact) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    //background
    QPixmap myBackGround("background2.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);

     Data MyDataBase;
     this->myID = MyConstants::getMyId().toInt();

     QString curr = QString::number(this->myID);
     string cid = curr.toStdString();
          string userCol     =  "UserID,FirstName,LastName,ProfilePicture";
          string userTable     =  "USER" ;
          string userCond     =  ";";
          this->data= MyDataBase.SelectData(userTable,userCol,userCond);
           cout<< "size is "<< data.size();

          string contactCol       =  "UserID, ContactID";
          string contactTable     =  "CONTACTS" ;
          string contactCond      =  "where UserID ='"+cid+"' ;";
          this->cdata= MyDataBase.SelectData(contactTable,contactCol,contactCond);

//          for(auto row1 : this->data) {
//               qDebug()<< row1;
//          }


          for(auto row1 : this->data) {
              bool found=0;
               if(row1[0]==curr)
                   continue;
              for(auto row2 : this->cdata) {
                  if(row1[0]==row2[1]){
                      found=1;
                      break;
                  }
          }

              if(found){
                    ContactWidget *mycontact = new ContactWidget();
                    QString myphotopath = "D:/Pictures/My Gallery/ACM/FB_IMG_1645480394683.jpg";
                    mycontact->setContactData(myphotopath, row1[1] +" "+ row1[2], "ID: "+row1[0]);
                    int w = mycontact->width();
                    int h = mycontact->height();
                    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
                    item->setSizeHint(QSize(w, h));
                    ui->listWidget->setItemWidget(item, mycontact);
                    ui->listWidget->scrollToBottom();
              }

          }
}

ShowContact::~ShowContact() {
    delete ui;
}

void ShowContact::on_pushButton_clicked()
{
    this->close();
}

