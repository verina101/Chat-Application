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
    //myData.CreateTables();
    //myData.UpdateData("PARTICIPATE", "Time = datetime('now') ","WHERE ChatRoomID = '2' AND UserID = '1' ");


    return APP.exec();
}
