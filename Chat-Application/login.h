#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Chats.h"
#include"Data.h"
#include<constantdata.h>
#include<string>
#include<iostream>
using namespace std;

namespace Ui {
class login;
}

class login : public QWidget {
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();


private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_submit_clicked();

    void on_pushButton_change_pic_clicked();

    void on_pushButton_clicked();


private:
    Ui::login *ui;
       Data db;
       string ProfilePicture;

};

#endif // LOGIN_H
