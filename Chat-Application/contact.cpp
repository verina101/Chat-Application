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
#include "contactwidget.h"
//#include <QPair>
using namespace std;
contact::contact(QWidget *parent): QWidget(parent), ui(new Ui::contact) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    //background
    QPixmap myBackGround("background2.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);


     QPixmap pix("D:/Pictures/My Gallery/ACM/FB_IMG_1645480394683.jpg") ;
     int h= ui->label->height();
     int w = ui->label->width();
     ui->label-> setPixmap(pix.scaled(w,h, Qt::IgnoreAspectRatio));
     Data MyDataBase;

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
                  mycontact->setContactData(defaultphoto, row1[1] +" "+ row1[2], "ID: Not Public");
                  }
                  else{
                  mycontact->setContactData(myphotopath, row1[1] +" "+ row1[2], "ID: "+row1[0]);
                  }
                  int w = mycontact->width();
                  int h = mycontact->height();
                  QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
                  item->setSizeHint(QSize(w, h));
                  ui->listWidget->setItemWidget(item, mycontact);
                  ui->listWidget->scrollToBottom();

                  this->at[expected++]=real;
              }
              real++;
          }



}

contact::~contact()
{
    delete ui;
}

//void contact::setMyId(int id){
//    this->myID = id;
//}



string ConvertoValue(string s) {
    s = "'" + s + "'" ;
    return s;
}

void contact::on_pushButton_2_clicked()
{
    QString s = QString::number(this->myID);
    string id = s.toStdString();
    //('A', 'B', '12', '123', 'N')
    int indx = ui->listWidget->selectionModel()->currentIndex().row();
    indx= at[indx];
    //************************************************
   // ui->listWidget->selectionModel()->Clear;
    ui->listWidget->selectAll();

   // while((tmpo = ui->listWidget->takeItem(cnto)) != nullptr) {

    //        cerr << cnto;
    //        cnto ++;
    //        if(cnto == 10) break;
    //    }
        // 1 3
//        ui->listWidget->clear();
//       int cnt = ui->listWidget->count();
//        for(int i=0 ;i <cnt;i++){

//            QListWidgetItem *item = ui->listWidget->item(i);
//            delete item;
//    }

//    ui->listWidget->clearSelection();
//   // ui->listWidget.select

//         ui->listWidget->selectAll();
//         QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

//         foreach(QListWidgetItem* item, items){
//             ui->listWidget->removeItemWidget(item);
//             delete item; // Qt documentation warnings you to destroy item to effectively remove it from QListWidget.
//         }
//         qDeleteAll(ui->listWidget->selectedItems());
//        foreach(QListWidgetItem * item, items)
//        {
//            delete ui->listWidget->takeItem(ui->listWidget->row(item));
//        }


    //**************************************
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
}




void contact::on_pushButton_clicked() {
//    Data MyDataBase;

//    cout<< "size of stack is" <<MyDataBase.s.size();
//    if(MyDataBase.s.empty())
//        this->close();
//    else{

//  char x= MyDataBase.s.top();
//  MyDataBase.s.pop();
//  if(x=='w'){
//    hide();
//     m->show();
//  }
//  else{
//      hide();
//      f->show();
//  }
//  }
    this->close();


}

