#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <QString>
#include <string>
#include "Data.h"
using namespace std;
namespace Ui {
class contact;
}

class contact : public QWidget
{
    Q_OBJECT

public:
   // map<pair<QString,QString>,bool> relation;
    explicit contact(QWidget *parent = nullptr);
    //void setMyId(int id);
    ~contact();

private slots:
    void  on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::contact *ui;
    vector<vector<QString>>data;
    vector<vector<QString>>cdata;
    int myID = 3;
    int at[500]={};

};

#endif // CONTACT_H
