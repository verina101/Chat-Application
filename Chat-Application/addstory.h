#ifndef ADDSTORY_H
#define ADDSTORY_H

#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <vector>
#include <QString>
#include <string>
#include "Data.h"
#include "MyConstants.h"
//#include<QDialog>

using namespace std;
namespace Ui {
class AddStory;
}

class AddStory : public QWidget
{
    Q_OBJECT

public:
    explicit AddStory(QWidget *parent = nullptr);
    static string EditText(string s);
    static string currDateTime();
    ~AddStory();

private slots:
    void on_pushButton_clicked();

    void on_radioButtonPhoto_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddStory *ui;
    vector<vector<QString>>data;
    int myID =(MyConstants::getMyId()).toInt();

};

#endif // ADDSTORY_H
