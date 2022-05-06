#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <Message.h>
#include "ChatRoom.h"

#include "Data.h"
using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
    ChatRoom win;
    win.show();



    return APP.exec();
}
