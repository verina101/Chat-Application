#include "profile.h"
#include "ui_profile.h"
#include "Data.h"
#include"login.h"
#include<constantdata.h>
#include<QMessageBox>
#include <qdebug.h>
#include<QPixmap>
#include<QFileDialog>
profile::profile(QWidget *parent): QWidget(parent), ui(new Ui::profile) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    QPixmap myBackGround("background2.png");
    ui->label->setPixmap(myBackGround.scaled(100,100,Qt::KeepAspectRatio));

    ui->comboBox_visibilty->addItem("For Contacts Only");//0
    ui->comboBox_visibilty->addItem("Everyone");//1

    constantdata currUser;
    string phoneno= currUser.getphoneNumber();
    Data myData;
    string userCol     =  "FirstName,LastName,ProfilePicture,Description,PhoneNumber,Visibility";
    string userTable     =  "USER" ;
    string userCond     =  "where PhoneNumber ='"+phoneno+"' ;";
    this->data= myData.SelectData(userTable,userCol,userCond);

        ui->label_name_2->setText(data[0][0]+ " "+ data[0][1]);
        ui->lineEdit->setText(data[0][3]);
        ui->label_phoneNumber->setText(data[0][4]);
        if(data[0][5]=="1")
            ui->comboBox_visibilty->setCurrentIndex(1);


        string path= data[0][2].toStdString(),name="";

        for(int i=path.size() - 1; i>-1; --i){
            if(path[i] == '/') break;

                 name = path[i] + name;

        }

        cout<< "full path "<< path<< endl<< "name " << name;
        QPixmap photo(QString::fromStdString(path));
        int h= ui->label->height();
        int w= ui->label->width();
        ui->label-> setPixmap(photo.scaled(w,h, Qt::IgnoreAspectRatio));

}
profile::~profile(){
    delete ui;
}

void profile::on_pushButton_clicked()
{
    QString filter="Jpeg File(*.jpeg);; Png File(*.png);; JPG File(*.jpg) ;; BMP File(*.bmp);; GIF file(*.gif)";
    filePath=QFileDialog::getOpenFileName(this,"open a file","D:/",filter);
    QMessageBox::information(this,"..",filePath);
    if(!filePath.isEmpty()){
    QPixmap pic(filePath);
    ui->label->setPixmap(pic.scaled(100,100,Qt::IgnoreAspectRatio));
     QFileInfo fi(filePath);
     QString fileName= fi.fileName();
     QString desktopPath = "";
     QString destinationPath= desktopPath+QDir::separator()+fileName;
    QFile::copy(filePath, destinationPath);
    }
}


void profile::on_pushButton_2_clicked()
{
    constantdata currUser;
    string phoneno= currUser.getphoneNumber();
    Data myData;
    string userCol     =  "ProfilePicture,Description";
    string userTable     =  "USER" ;
    string userCond     =  ";";

    if(!filePath.isEmpty()){
    userCol = "ProfilePicture = '" + filePath.toStdString() + "'";
    myData.UpdateData(userTable, userCol, userCond);
    }

    QString desk= ui->lineEdit->text();
    userCond = "WHERE PhoneNumber = '" + phoneno + "'";
    userCol= "Description = '" + desk.toStdString() + "'";
    myData.UpdateData(userTable, userCol, userCond);

    QString visibility = ui->comboBox_visibilty->currentText();
    visibility = visibility.contains("Everyone") ? "1" : "0";
    userCond = "WHERE PhoneNumber = '" + phoneno + "'";
    userCol= "Visibility = '" + visibility.toStdString() + "'";
    myData.UpdateData(userTable, userCol, userCond);


    Chats *myChats = new Chats();
    myChats->show();
    this->close();
}

