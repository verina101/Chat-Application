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
#include "Datetime.h"
#include "mainwindow.h"
#include <showstories.h>
#include <StoryTime.h>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);
  //  Data db;
   // db.CreateTables();


    login Win;
    Win.show();

    return APP.exec();
}
