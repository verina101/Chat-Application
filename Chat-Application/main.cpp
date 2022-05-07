#include "Data.h"
#include "mainwindow.h"
#include "ChatRoom.h"
#include "ChatInfo.h"
#include <Message.h>

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QVector>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);

    //Data DataBase;
    //DataBase.CreateTables();

    ChatRoom win;
    win.show();



    return APP.exec();
}
