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



void ShowContact::on_listWidget_currentRowChanged(int currentRow){

    selectedID = cdata[currentRow][1];

}

void ShowContact::openShowContact()
{


    this->myID = MyConstants::getMyId().toInt();

     QString curr = QString::number(this->myID);
     string cid = curr.toStdString();
          string userCol     =  "UserID,FirstName,LastName,ProfilePicture";
          string userTable     =  "USER" ;
          string userCond     =  ";";
          this->data= db.SelectData(userTable,userCol,userCond);
           cout<< "size is "<< data.size();

          string contactCol       =  "UserID, ContactID";
          string contactTable     =  "CONTACTS" ;
          string contactCond      =  "where UserID ='"+cid+"' ;";
          this->cdata= db.SelectData(contactTable,contactCol,contactCond);


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
                    //ui->listWidget->scrollToBottom();
              }

          }
}

void ShowContact::on_listWidget_itemClicked(QListWidgetItem *item){

    vector<QString> userData = db.SelectData("USER","FirstName, LastName","WHERE UserID = " + db.convertToValue(selectedID)).front();
    QString chatName1 = MyConstants::getMyId() + "#" + selectedID;
    QString chatName2 = selectedID + "#" +MyConstants::getMyId();
    vector<vector<QString>> myChatID = db.SelectData("CHATROOM", "RoomID", "WHERE Name in ("+ db.convertToValue(chatName1)+", "+db.convertToValue(chatName2)+")" );

    if(myChatID.empty()){

        db.InsertData("CHATROOM","( " + db.convertToValue(chatName1) + " )");
        QString chatID = db.SelectData("CHATROOM","RoomID","ORDER BY RoomID DESC").front().front();
        db.InsertData("CHATROOMINFO","( " + db.convertToValue(chatID) +", 'None', '2', '0' )");
        db.InsertData("PARTICIPATE","( " + db.convertToValue(chatID) + ","+ db.convertToValue(MyConstants::getMyId()) +" , datetime('now') )");
        db.InsertData("PARTICIPATE","( " + db.convertToValue(chatID) + ","+ db.convertToValue(selectedID) +" , datetime('now') )");

        MyConstants::setMyChatRoomID(chatID);


    }else{

        MyConstants::setMyChatRoomID(myChatID[0][0]);

    }

    MyConstants::setMyChatRoomName(userData[0] + " " + userData[1]);
    emit openContactChat();
    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

}
