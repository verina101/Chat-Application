#ifndef MYMESSAGE_H
#define MYMESSAGE_H

#include <qplaintextedit.h>
#include <QWidget>
#include <Message.h>

#include <QString>
using namespace std;

namespace Ui {
class MyMessage;
}

class MyMessage: public Message
{
    Q_OBJECT

public:
    explicit MyMessage(QWidget *parent = nullptr);
    ~MyMessage();

private:

    Ui::MyMessage *ui;
};

#endif // MYMESSAGE_H
