#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <QString>
#include <string>
#include <QListWidgetItem>
#include "Data.h"
#include "MyConstants.h"

//#include<QDialog>

using namespace std;
namespace Ui {
class contact;
}

class contact : public QWidget
{
    Q_OBJECT

public:
    explicit contact(QWidget *parent = nullptr);
    ~contact();

    Data *w= new Data;
    Data *f= new Data;

private slots:
    void  on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void openAddContact();

signals:
    void exitAddContact();


private:
    Ui::contact *ui;
    vector<vector<QString>>data;
    vector<vector<QString>>cdata;
    int myID = (MyConstants::getMyId()).toInt();
    int at[500]={};
    bool isSelected = false;

};

#endif // CONTACT_H
