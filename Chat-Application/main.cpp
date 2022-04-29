#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include "Data.h"
using namespace std;

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

    Data MyDataBase;
    MyDataBase.CreateTables();


    return APP.exec();
}
