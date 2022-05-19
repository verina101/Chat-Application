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
#include "Chats.h"
#include "contactwidget.h"
//#include <QPair>
using namespace std;
contact::contact(QWidget *parent): QWidget(parent), ui(new Ui::contact) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

}

contact::~contact()
{
    delete ui;
}

string ConvertoValue(string s) {
    s = "'" + s + "'" ;
    return s;
}

void contact::on_pushButton_2_clicked()
{
    if(!this->isSelected)
        return;

    QString s = QString::number(this->myID);
    string id = s.toStdString();
    //('A', 'B', '12', '123', 'N')
    int indx = ui->listWidget->selectionModel()->currentIndex().row();
    indx= at[indx];

    QListWidgetItem *it = ui->listWidget->currentItem();
    Data db;
    string tablename ="Contacts";
    string col = "(UserID,ContactID) ";
    QString x = data[indx][0];
    string str=x.toStdString();

    string val1 = "('"+ id +"','"+str+"');";
    string val2 = "('"+ str +"','"+id+"');";

    db.InsertData(tablename,val1);
    db.InsertData(tablename,val2);
    delete it ;
    this->isSelected = false;
}


void contact::on_pushButton_clicked() {

    emit exitAddContact();
    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

}


void contact::on_listWidget_itemClicked(QListWidgetItem *item){
    this->isSelected = true;
}

void contact::openAddContact()
{


    //background
    QPixmap myBackGround(":/images/assets/app_BackGround.jpg");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);


     QPixmap pix("D:/Pictures/My Gallery/ACM/FB_IMG_1645480394683.jpg") ;
     int h= ui->label->height();
     int w = ui->label->width();
     ui->label-> setPixmap(pix.scaled(w,h, Qt::IgnoreAspectRatio));
     Data MyDataBase;

     this->myID = MyConstants::getMyId().toInt();
     QString curr = QString::number(this->myID);
     string cid = curr.toStdString();
          string userCol     =  "UserID,FirstName,LastName,ProfilePicture,Visibility";
          string userTable     =  "USER" ;
          string userCond     =  ";";
          this->data= MyDataBase.SelectData(userTable,userCol,userCond);
           //cout<< "size is "<< data.size();

          string contactCol       =  "UserID,ContactID";
          string contactTable     =  "CONTACTS" ;
          string contactCond      =  "where UserID ='"+cid+"' ;";
          this->cdata= MyDataBase.SelectData(contactTable,contactCol,contactCond);

          for(auto row1 : this->data) {
               qDebug()<< row1;
          }



          int expected=0, real=0,visible=0;
          QString seen = QString::number(visible);
          memset(at, 0, sizeof at);
          for(auto row1 : this->data) {
              bool found=0;
               if(row1[0]==curr)
                   found=1;
              for(auto row2 : this->cdata) {
                  if(row1[0]==row2[1]){
                      found=1;
                      break;
                  }
          }

              if(!found){
                  ContactWidget *mycontact = new ContactWidget();
                  QString myphotopath = "D:/Pictures/My Gallery/ACM/FB_IMG_1645480394683.jpg";  //row1[3]
                  QString defaultphoto= "D:/Pictures/Ds project/NotSeenBackground.png";
                  if(row1[4]==seen){
                  mycontact->setContactData(defaultphoto, row1[1] +" "+ row1[2], "ID: "+row1[0]);
                  }
                  else{
                  mycontact->setContactData(myphotopath, row1[1] +" "+ row1[2], "ID: "+row1[0]);
                  }
                  int w = mycontact->width();
                  int h = mycontact->height();
                  QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
                  item->setSizeHint(QSize(w, h));
                  ui->listWidget->setItemWidget(item, mycontact);
                  //ui->listWidget->scrollToBottom();

                  this->at[expected++]=real;
              }
              real++;
          }

}

