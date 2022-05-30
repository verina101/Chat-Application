#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include"Data.h"
#include<vector>
#include<iostream>
#include<string>
using namespace std;
namespace Ui {
class profile;
}

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::profile *ui;
    vector<vector<QString>> data;
    QString filePath;
};

#endif // PROFILE_H
