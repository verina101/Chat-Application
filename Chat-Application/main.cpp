#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <QDebug>
#include <qdebug.h>
#include "Data.h"

using namespace std;


int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
    MainWindow win;
    win.show();

    Data MyDataBase; // create your database
    MyDataBase.CreateTables(); // create all tables

    //create users
    //(FirstName, LastName, ProfilePicture, Description, Password, PhoneNumber, Visibility)
    string tableName = "USER";
    string columns = "*";
    string values = "('Maria', 'Tawfek', 'NA', 'Available', 'abcd', '01478523699', 'f')";
    string empty = "";
    //MyDataBase.InsertData(tableName, columns, values);

    vector<vector<QString>> vec = MyDataBase.SelectData(tableName, columns, empty);
    MyDataBase.DisplayData(vec);

    return APP.exec();
}
