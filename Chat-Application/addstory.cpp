#include "addstory.h"
#include "ui_addstory.h"
#include <iostream>
#include "Chats.h"
#include "Data.h"
#include <QMessageBox>
#include<QDateTime>
#include <chrono>
#include <ctime>
#define _GNU_SOURCE //to remove warning: implicit declaration of ‘strptime’
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <QFileDialog>
#include "dateTime.h"
using namespace std;
AddStory::AddStory(QWidget *parent): QWidget(parent), ui(new Ui::AddStory) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));
}

AddStory::~AddStory()
{
    delete ui;
}


string AddStory :: currDateTime(){
    time_t now = time(0);
    dateTime t;
    char *dt = ctime(&now);
    string s2(dt);
    return s2;
}

string  AddStory:: EditText(string s){
    string str;
    for(int i =0 ; i < (int)s.size();i++){
        if(s[i]==' ' || s[i]=='\n')continue;
        else{
            for(int j = i ; j < (int)s.size(); j++){
                str.push_back(s[j]);
            }
            break;
        }
    }

    for(int i =str.size() ; i > -1 ;i--){
        if(str[i]==' ' || str[i]=='\n')
            str.pop_back();
        else
            break;
    }

    return str;
}




void AddStory::on_pushButton_clicked(){
    QString input    = ui->textEdit->toPlainText();
    string editInput = input.toStdString();
    string str       = this->EditText(editInput);
    bool photo = ui->radioButtonPhoto->isChecked();
    bool text  = ui->radioButtonText->isChecked();


    if((!photo&&!text) || !str.size()) {
        QMessageBox :: warning(this, "Add Story", "Invalid Data !");
    }
    else {
        QString s = QString::number(this->myID);
        string id = s.toStdString();
        Data MyDatabase;

        string userCol       =  "FirstName, LastName";
        string userTable     =  "USER" ;
        string userCond      =  "where UserID ='"+id+"' ;";
        this->data= MyDatabase.SelectData(userTable,userCol,userCond);


        string Name = this->data[0][0].toStdString();
        string lastName  = this->data[0][1].toStdString();
        Name+=" "+lastName;
        string tableName = "STORY";
        string story = (photo)? str : "0";
        string t = (text )? str : "0";
        string DateTime = currDateTime();
        string col="*";
        string cond=  "where StoryOwnerID ='"+id+"' ;";
        string values = "('"+id+"',"+"'"+Name+"','"+t+"','"+story+"','"+DateTime+"' )";
        MyDatabase.InsertData(tableName,values);
        QMessageBox :: information(this, "Add Story", "Story Added Successfully");
        ui->textEdit->setPlainText("");



    }
}


void AddStory::on_radioButtonPhoto_clicked()
{
    ui->textEdit->clear();
    QString fileName= QFileDialog:: getOpenFileName(this, "open a file","D://",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
    QMessageBox :: information(this, "..", fileName);
    ui->textEdit->setText(fileName);
    ui->textEdit->setReadOnly(true);

}


void AddStory::on_pushButton_2_clicked()
{
    Chats *myChats = new Chats();
    myChats->show();
    this->close();
}

void AddStory::on_pushButton_4_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_4->text());
    }

}


void AddStory::on_pushButton_12_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_12->text());

    }

}


void AddStory::on_pushButton_13_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_13->text());

    }
}


void AddStory::on_pushButton_8_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_8->text());

    }
}


void AddStory::on_pushButton_3_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_3->text());

    }
}


void AddStory::on_pushButton_5_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_5->text());

    }
}


void AddStory::on_pushButton_11_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_11->text());

    }
}


void AddStory::on_pushButton_9_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_9->text());

    }
}


void AddStory::on_pushButton_6_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_6->text());

    }
}


void AddStory::on_pushButton_7_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_7->text());

    }
}


void AddStory::on_pushButton_10_clicked()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit->insertPlainText(ui->pushButton_10->text());

    }
}

void AddStory::on_radioButtonText_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->setReadOnly(false);
}

