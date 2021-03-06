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

contact::~contact() {
    delete ui;
}

string ConvertoValue(string s) {
    s = "'" + s + "'" ;
    return s;
}

void contact::on_pushButton_2_clicked() {
    if(!this->isSelected) return;

    QString s = QString::number(this->myID);
    string id = s.toStdString();
    int indx = ui->listWidget->selectionModel()->currentIndex().row();
    indx= at[indx];
    Data db;
    string tablename ="Contacts";
    string col = "(UserID,ContactID) ";
    QString x = data[indx][0];
    string str=x.toStdString();

    string val1 = "('"+ id +"','"+str+"');";
    string val2 = "('"+ str +"','"+id+"');";

    db.InsertData(tablename,val1);
    db.InsertData(tablename,val2);
    ui->listWidget->item(ui->listWidget->currentRow())->setHidden(true);
    this->isSelected = false;
}


void contact::on_pushButton_clicked() {
    emit exitAddContact();
    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

}


void contact::on_listWidget_itemClicked(QListWidgetItem *item){
    item->isHidden();
    this->isSelected = true;
}

void contact::openAddContact() {
    QPixmap pix(":/images/assets/contact.png") ;
    int h= ui->label->height();
    int w = ui->label->width();
    ui->label-> setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    Data MyDataBase;

    this->myID = MyConstants::getMyId().toInt();
    QString curr = QString::number(this->myID);

    string cid = curr.toStdString();
    string userCol     =  "UserID,FirstName,LastName,ProfilePicture,Visibility";
    string userTable     =  "USER" ;
    string userCond     =  ";";
    this->data= MyDataBase.SelectData(userTable,userCol,userCond);

    string contactCol       =  "UserID,ContactID";
    string contactTable     =  "CONTACTS" ;
    string contactCond      =  "where UserID ='"+cid+"' ;";
    this->cdata= MyDataBase.SelectData(contactTable,contactCol,contactCond);

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
            QString defultProfile = ":/images/assets/defultProfile.png";
            if(row1[4]==seen){
                mycontact->setContactData(defultProfile, row1[1] +" "+ row1[2], "ID: "+row1[0]);
            }
            else{
                mycontact->setContactData(row1[3], row1[1] +" "+ row1[2], "ID: "+row1[0]);
            }
            int w = mycontact->width();
            int h = mycontact->height();
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            item->setSizeHint(QSize(w, h));
            ui->listWidget->setItemWidget(item, mycontact);

            this->at[expected++]=real;
        }
        real++;
    }

}

