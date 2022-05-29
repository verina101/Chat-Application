#ifndef STORYTIME_H
#define STORYTIME_H
#include <QWidget>
#include <QtSql>
#include <iostream>
#include <QVector>
#include <vector>
#include <QString>
#include <string>
#include "Data.h"

using namespace std;

namespace Ui {
class StoryTime;
}

class StoryTime : public QWidget
{
    Q_OBJECT

public:
    explicit StoryTime(QWidget *parent = nullptr);
    ~StoryTime();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::StoryTime *ui;
};

#endif // STORYTIME_H
