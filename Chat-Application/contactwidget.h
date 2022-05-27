#ifndef CONTACTWIDGET_H
#define CONTACTWIDGET_H

#include <QWidget>
#include<iostream>
#include<string>
using namespace std;
namespace Ui {
class ContactWidget;
}

class ContactWidget : public QWidget
{
    Q_OBJECT
    string picture;
    string name;
    string id;
public:
    explicit ContactWidget(QWidget *parent = nullptr);
    ~ContactWidget();

    void setContactData(QString pic ,QString name , QString id);

private:
    Ui::ContactWidget *ui;
};

#endif // CONTACTWIDGET_H
