#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <bits/stdc++.h>
#include "login.h"
#include "ChatRoom.h"
#include "Data.h"
#include "contact.h"
#include "showcontact.h"
#include "addstory.h"
#include "saveddata.h"
#include "showcontactnamestory.h"
#include "Datetime.h"
#include <showstories.h>
#include <StoryTime.h>
#include <profile.h>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
    Data myData;
    //dateTime obj;
   // DateTime t;
    myData.CreateTables();
//    string s ="Mon May 15 13:23:52 2022";
//    if(t.isValidStory(s))cout<<"YES"<<endl;
//    else cout<<"NO"<<endl;

//    string tableName="USER";
//    string val="('Amir','Moris','123','01234567890','12340','145600','0')";
//    myData.InsertData(tableName,val);

//    string tableName="STORY";
//       string val="('3','Amir Moris','1','0','Wed May 10 23:35:30 2022')";
//       myData.InsertData(tableName,val);


    profile Win;
    Win.show();
    return APP.exec();
}
