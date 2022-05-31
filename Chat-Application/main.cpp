#include <QApplication>
#include <QCoreApplication>

#include "login.h"
#include "Data.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication APP(argc, argv);

    Data db;
    db.CreateDataBase();

    login Win;
    Win.show();

    return APP.exec();
}
