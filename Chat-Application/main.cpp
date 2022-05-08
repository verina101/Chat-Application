#include "login.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include "ChatRoom.h"
#include "Data.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
    login win;
    win.show();
    Data myData;
    myData.CreateTables();
    //myData.InsertData("PARTICIPATE", "( '1', '1' , datetime('now') )");
//    myData.InsertData("PARTICIPATE", " ('1', '2' , datetime('now') )");
//    myData.InsertData("Message", " ('1' , '1', 'verina','first hello','0' )");
//    myData.InsertData("Message", "( '2' , '1', 'amir','first hello','0' )");
    return APP.exec();
}
