#ifndef ADDSTORY_H
#define ADDSTORY_H

#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <vector>
#include <QString>
#include <string>
#include <QGraphicsScene>
#include "Data.h"
#include "MyConstants.h"

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

    void on_pushButton_4_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_radioButtonText_clicked();

private:
    Ui::AddStory *ui;
    vector<vector<QString>>data;
    int myID =(MyConstants::getMyId()).toInt();


};

#endif // ADDSTORY_H
