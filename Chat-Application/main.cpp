#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include "Data.h"
using namespace std;

void printvalues(vector<vector<QString>> v) {
    for(auto row : v) {
        for(auto col : row) {
            qDebug() << col ;
        }
        cout<<"\n";
    }
}
int ConverToInteger(string str) {
    return stoll(str, nullptr, 10);
}
string ConverToInteger(int num) {
    return to_string(num);
}
int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
    MainWindow win;
    win.show();

    Data MyDataBase; // create your database
    MyDataBase.CreateTables(); // create all tables



    return APP.exec();
}
