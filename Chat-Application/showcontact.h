#ifndef SHOWCONTACT_H
#define SHOWCONTACT_H

#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <QString>
#include <string>
#include <QListWidgetItem>
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

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_itemClicked(QListWidgetItem *item);
    void openShowContact();

signals:
    void exitShowContact();
    void openContactChat();

private:
    Ui::ShowContact *ui;
    int myID = (MyConstants::getMyId()).toInt();
    vector<vector<QString>>cdata;
    vector<vector<QString>>data;
    Data db;
    QString selectedID = "";


};

#endif // SHOWCONTACT_H
