#include "addstory.h"
#include "ui_addstory.h"
#include <iostream>
#include "Data.h"
#include <QMessageBox>
#include<QDateTime>
#include <chrono>
#include <ctime>
#define _GNU_SOURCE //to remove warning: implicit declaration of ‘strptime’
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
AddStory::AddStory(QWidget *parent): QWidget(parent), ui(new Ui::AddStory) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    QPixmap myBackGround("background2.png");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);
}

AddStory::~AddStory()
{
    delete ui;
}

/*

char* time1 = "2014/02/12 13:26:33"; // end
    char* time2 = "2014/02/14 11:35:06"; // beg
    struct tm tm1, tm2; // intermediate datastructes
    time_t t1, t2; // used in difftime

    //(1) convert `String to tm`:  (note: %T same as %H:%M:%S)
    if(strptime(time1, "%Y/%m/%d %T", &tm1) == NULL)
       printf("\nstrptime failed-1\n");
    if(strptime(time2, "%Y/%m/%d %T", &tm2) == NULL)
       printf("\nstrptime failed-2\n");

    //(2) convert `tm to time_t`:
    t1 = mktime(&tm1);
    t2 = mktime(&tm2);
    //(3) Convert Seconds into hours
    double hours = difftime(t2, t1)/60/60;
    printf("%lf\n", hours);
    // printf("%d\n", (int)hours); // to display 46

*/





string AddStory :: currDateTime(){
    auto start = chrono::system_clock::now();
        // Some computation here
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds = end-start;

       // time_t end_time = chrono::system_clock::to_time_t(end);

        // string dateTime=(string)ctime(&end_time);
           string dateTime="";
        return dateTime;
}

string  AddStory:: EditText(string s){

    string str;
    for(int i =0 ; i < s.size();i++){
        if(s[i]==' ' || s[i]=='\n')continue;
        else{
            for(int j = i ; j <s.size(); j++){
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




void AddStory::on_pushButton_clicked()
{

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
            //cout<<Name<<endl;
            string tableName = "STORY";
            string story = (photo)? str : "0";
            string t = (text )? str : "0";
            string DateTime = currDateTime();
            string col="*";
            string cond=  "where StoryOwnerID ='"+id+"' ;";
          //  vector<vector<QString>>show;
            //cout<< DateTime<<endl;
           // DateTime.pop_back();
             //DateTime.pop_back();
               // cout << "finished computation at " << std::ctime(&end_time)
            string values = "('"+id+"',"+"'"+Name+"','"+t+"','"+story+"','"+DateTime+"','0'"+")";
           // MyDatabase.InsertData(tableName,values);
          //show = MyDatabase.SelectData(tableName,col,cond);


            QMessageBox :: information(this, "Add Story", "Valid Data !");
        }
}

