#ifndef SHOWCONTACT_H
#define SHOWCONTACT_H

#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <QString>
#include <string>
#include "Data.h"
#include "contactwidget.h"
#include "MyConstants.h"
//#include<QDialog>

using namespace std;
namespace Ui {
class ShowContact;
}

class ShowContact : public QWidget
{
    Q_OBJECT

public:
    explicit ShowContact(QWidget *parent = nullptr);
    ~ShowContact();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShowContact *ui;
    int myID = 1;
    vector<vector<QString>>cdata;
    vector<vector<QString>>data;
};

#endif // SHOWCONTACT_H
