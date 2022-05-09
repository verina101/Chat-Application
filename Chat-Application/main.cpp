#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include "Data.h"
#include "contact.h"
#include "showcontact.h"
#include "addstory.h"
#include "saveddata.h"
#include <ctime>
#include "showcontactnamestory.h"
using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);

    Data MyDataBase;
    MyDataBase.CreateTables();




//    string id        = "3";
//    string Name      = "Amir Moris";
//    string tableName = "STORY";
//    string story     = "aaaa";
//    string t         = "zzz";
//    string DateTimee = "2021";
//    string values = "('"+id+"',"+"'"+Name+"','"+t+"','"+story+"','"+DateTimee+"' )";
//    //cout<<values<<endl;
//     MyDataBase.InsertData(tableName,values);

    // *********************************************** //

//        string table="USER";
//        string val="('Amir', 'Moris', '111', '222', '123456', '01125874639', '1');";
//        MyDataBase.InsertData(table,val);

//        string tabl="CONTACTS";
//        string val= "('1','3');";
//        MyDataBase.InsertData(tabl,val);



    MainWindow w;
    contact c;
    ShowContact sc;
    AddStory a;
    ShowContactNameStory showContact ;
  // showContact.show();
    a.show();
  // sc.show();
    //w.show();
  //  c.show();
   // string timee =a.currDateTime()
    //to_time_t(timee);


    return APP.exec();
}


/*
#include <stdio.h>
void main()
{
    char* date1 = "9\\12\\2012";
    char* date2 = "6\\11\\2013";

    int day1,month1,year1;
    int day2,month2,year2;


    if (year1<year2 || month1<month2 || day1<day2) //compares 2 dates
    {
        printf("date1 < date2\n");
    }
    else
    {
        printf("date1 >= date2\n");
    }

    char newdate[15];

    sprintf(newdate,"%d\\%d\\%d",13,2,1998); //make a date string from numbers
    printf("%s\n",newdate);
}


*/
