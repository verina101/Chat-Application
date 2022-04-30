#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include "Data.h"
#include "contact.h"
using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
    MainWindow win;
    Data MyDataBase;
    contact c;
    //win.show();
    c.show();
    MyDataBase.CreateTables();

//    string table="USER";
//    string val="('lina-verina', 'micheal', '111', '222', '123456', '0125874639000', '1');";
//    MyDataBase.InsertData(table,val);

//    string tabl="CONTACTS";
//    string val= "('1','2');";
//    MyDataBase.InsertData(tabl,val);




    return APP.exec();
}
