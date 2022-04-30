#include "contact.h"
#include "ui_contact.h"
#include <QPixmap>
#include "mainwindow.h"
#include "contact.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include "Data.h"
#include <QMap>
//#include <QPair>
using namespace std;
contact::contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contact)
{
    ui->setupUi(this);
     QPixmap pix("D:/Pictures/Ds project/download.png") ;
     ui->label-> setPixmap(pix);
     Data MyDataBase;

     QString curr = QString::number(this->myID);
     string cid = curr.toStdString();
          string Col       =  "UserID,FirstName,LastName";
          string table     =  "USER" ;
          string cond      =  ";";
          this->data= MyDataBase.SelectData(table,Col,cond);
           //cout<< "size is "<< data.size();
          string cCol       =  "UserID,ContactID";
          string ctable     =  "CONTACTS" ;
          string ccond      =  "where UserID ='"+cid+"' ;";
          this->cdata= MyDataBase.SelectData(ctable,cCol,ccond);

          for(auto row1 : this->cdata) {
               qDebug()<< row1;
          }



          int expected=0, real=0;
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
                  ui->listWidget->addItem("\n" + row1[1] +" "+ row1[2]+"\n"+ "ID : "+ row1[0]+ "\n") ;
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


void  contact::on_pushButton_clicked()
{
      this->close();
 }


void contact::on_pushButton_2_clicked()
{
    QString s = QString::number(this->myID);
    string id = s.toStdString();
    //('A', 'B', '12', '123', 'N')
    int indx = ui->listWidget->selectionModel()->currentIndex().row();
    indx= at[indx];
    cout<< indx<< endl;
    qDebug()<< data[2][0];
    QListWidgetItem *it = ui->listWidget->currentItem();
    Data db;
    string tablename ="Contacts";
    string col = "(UserID,ContactID) ";
     QString x = data[indx][0];
     string str=x.toStdString();

     string val1 = "( ' "+ id +"' , ' " + str + "' );";
     string val2 = "( ' "+ str +"' , ' " + id + "' );";
     db.InsertData(tablename,val1);
     db.InsertData(tablename,val2);
     delete it ;
}

