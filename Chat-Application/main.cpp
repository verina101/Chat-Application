#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QVector>

#include "login.h"
#include "ChatRoom.h"
#include "Data.h"
#include "contact.h"
#include "showcontact.h"
#include "addstory.h"
#include "saveddata.h"
#include "showcontactnamestory.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
    Data myData;
    myData.CreateTables();

    login win;
    win.show();

    return APP.exec();
}

