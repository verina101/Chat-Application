#include "login.h"
#include "ui_login.h"
#include "Data.h"
#include "MyConstants.h"
#include<QMessageBox>
#include <qdebug.h>
#include<QPixmap>
#include<QFileDialog>

login::login(QWidget *parent): QWidget(parent), ui(new Ui::login) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    ui->stackedWidget_2->setCurrentIndex(0);
    ui->comboBox_visibilty->addItem("your contacts");//0
    ui->comboBox_visibilty->addItem("for any one");//1
    QPixmap pic("C:/Users/m/Pictures/Saved Pictures/WhatsApp Image 2022-05-05 at 11.19.27 PM.jpeg");
    ui->label_pic->setPixmap(pic.scaled(100, 100, Qt::KeepAspectRatio));

}

login::~login() {
    delete ui;
}

void login::on_pushButton_login_clicked() {
    QString mobileno,password;

    mobileno=ui->lineEdit_mobileno->text();
    password=ui->lineEdit_password->text();
   string tablename="USER",columns="UserID, PhoneNumber, Password";
   string condition="where PhoneNumber='"+mobileno.toStdString() +"' and Password='"+password.toStdString() +"' ";
   vector<vector<QString>> returndata=db.SelectData(tablename,columns,condition);
   if(returndata.empty()){
     QMessageBox::warning(this,"invalid login","wrong mobileno or password");
     //qDebug() << "wrong password or mobileno";
   }
   else{
       QMessageBox::information(this,"valid login","login successfully");
       MyConstants().myId = returndata[0][0].toStdString();
       ui->stackedWidget_2->close();
       close();
       myChats = new Chats();
       myChats->show();

   }
   db.DisplayData(returndata);
}

void login::on_pushButton_signup_clicked() {
    ui->stackedWidget_2->setCurrentIndex(1);

}

void login::on_pushButton_submit_clicked() {
    QString firstname,lastname,password,phoneno,description,visibility;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    password=ui->lineEdit_password_2->text();
    phoneno=ui->lineEdit_phoneno->text();
    description=ui->lineEdit_description->text();
    visibility=ui->comboBox_visibilty->currentText();

    visibility = visibility.contains("for any one") ? "1" : "0";

     if(firstname.isEmpty() || lastname.isEmpty() || description.isEmpty() || password.isEmpty() || phoneno.isEmpty()) {
       QMessageBox::warning(this,"invalid registration "," missing value");
     }
     else {
         if(lastname.size()<3 || firstname.size()<3){
             QMessageBox::warning(this,"invalid registration "," enter valid first or last name");
         }
         else{
         bool x = true;
         if(phoneno.size() == 11 && phoneno.toStdString()[0] == '0'){
             for(int i = 1; i <= 10; i++){
                 if(phoneno.toStdString()[i] >= '0' && phoneno.toStdString()[i] <= '9'){
                     x = true;
                     continue;
                 }
                 else{
                     x = false;
                     break;
                 }
             }
             if(x == true) {
             string columns = "PhoneNumber ";
             string condition = "where PhoneNumber = '" + phoneno.toStdString() + "'";
             vector<vector<QString>> returnData = db.SelectData("USER", columns, condition);
             if(returnData.empty()) {
                 string tablename="USER";
                 string values = "('" + firstname.toStdString() + "','" + lastname.toStdString() + "','not found','" + description.toStdString()+"','" + password.toStdString() + "','"+phoneno.toStdString() + "','"+visibility.toStdString() + "')";
                 db.InsertData(tablename,values);
                 QMessageBox::information(this, "valid registration", "registration successfully");
             }
             else{
                  QMessageBox::warning(this, "invalid registration ", " duplicated phone number");
             }
              }
             else{
                    QMessageBox::warning(this, "invalid registration ", " enter valid phone number integer only");
             }

         }
         else{
                QMessageBox::warning(this, "invalid registration ", " enter valid phone number start with 0 and size 11");
         }
      }
    }
}

void login::on_pushButton_change_pic_clicked() {
    QString filter = "Jpeg File(*.jpeg);; Png File(*.png)";
    QString filename = QFileDialog::getOpenFileName(this, "open a file", "D:/pic", filter);
    QMessageBox::information(this, "..", filename);
    QPixmap pic(filename);
    ui->label_pic->setPixmap(pic.scaled(100, 100, Qt::KeepAspectRatio));
}

