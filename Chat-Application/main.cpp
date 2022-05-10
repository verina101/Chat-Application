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
    //Data myData;
    //myData.CreateTables();


    login win;
    win.show();


    return APP.exec();
}
