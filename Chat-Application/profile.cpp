#include "profile.h"
#include "ui_profile.h"
#include "Data.h"
#include"login.h"
#include<constantdata.h>
#include<QMessageBox>
#include <qdebug.h>
#include<QPixmap>
#include<QFileDialog>
profile::profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
    //QPixmap pic("C:/Users/m/Pictures/Saved Pictures/WhatsApp Image 2022-05-05 at 11.19.27 PM.jpeg");
    //ui->label->setPixmap(pic.scaled(100,100,Qt::KeepAspectRatio));
    constantdata currUser;
    string phoneno= currUser.getphoneNumber();
    Data myData;
    string userCol     =  "FirstName,LastName,ProfilePicture,Description,PhoneNumber";
    string userTable     =  "USER" ;
    string userCond     =  "where PhoneNumber ='"+phoneno+"' ;";
    this->data= myData.SelectData(userTable,userCol,userCond);

    for(auto it: data)
    qDebug()<< it;
        ui->label_name_2->setText(data[0][0]+ " "+ data[0][1]);
        ui->lineEdit->setText(data[0][3]);
        ui->label_phoneNumber->setText(data[0][4]);


        string path= data[0][2].toStdString(),name="";
        bool p=false;
        for(int i=path.size(); i>-1; --i){
            if(path[i]=='/')
                break;
            if(path[i]=='.'){
                p=true;
                continue;
        }

            if(p)
               name+=path[i];
        }

        reverse(name.begin(), name.end());

        cout<< "full path "<< path<< endl<< "name " << name;
        QPixmap photo(QString::fromStdString(name));
        int h= ui->label->height();
        int w= ui->label->width();
        ui->label-> setPixmap(photo.scaled(w,h, Qt::IgnoreAspectRatio));

}
profile::~profile()
{
    delete ui;
}

void profile::on_pushButton_clicked()
{
    QString filter="Jpeg File(*.jpeg);; Png File(*.png);; JPG File(*.jpg) ;; BMP File(*.bmp);; GIF file(*.gif)";
    filePath=QFileDialog::getOpenFileName(this,"open a file","D:/pic",filter);
    QMessageBox::information(this,"..",filePath);
    if(!filePath.isEmpty()){
    QPixmap pic(filePath);
    ui->label->setPixmap(pic.scaled(100,100,Qt::KeepAspectRatio));
     QFileInfo fi(filePath);
     QString fileName= fi.fileName();
     QString desktopPath = "D:/chatapp/Chat-Application/build-Chat-Application-Desktop_Qt_6_3_0_MinGW_64_bit-Debug";
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
   // this->data= myData.SelectData(userTable,userCol,userCond);
    QString desk= ui->lineEdit->text();
    userCol = "ProfilePicture = '" + filePath.toStdString() + "'";
    userCond = "WHERE PhoneNumber = '" + phoneno + "'";
    myData.UpdateData(userTable, userCol, userCond);
    userCol= "Description = '" + desk.toStdString() + "'";
    myData.UpdateData(userTable, userCol, userCond);
    this->close();
}

