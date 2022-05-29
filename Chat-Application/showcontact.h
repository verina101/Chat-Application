#ifndef SHOWCONTACT_H
#define SHOWCONTACT_H

#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <QString>
#include <string>
#include <QListWidgetItem>
#include <set>
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
    int groupType=0;

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);
    void openShowContact();
    void on_listWidget_2_itemClicked(QListWidgetItem *item);
    void on_pushButton_creategroupChat_clicked();

signals:
    void exitShowContact();
    void openContactChat();

private:

    Ui::ShowContact *ui;
    int myID = (MyConstants::getMyId()).toInt();
    vector<vector<QString>>cdata;
    vector<vector<QString>>data;
    Data db;
    set<int>selectedIDs;


};

#endif // SHOWCONTACT_H
