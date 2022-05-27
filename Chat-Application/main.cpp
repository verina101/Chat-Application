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
#include"profile.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
//    Data myData;
//    myData.CreateTables();
//    login win;
//    win.show();

     profile p;
     p.show();


    login Win;
    Win.show();
    return APP.exec();
}
