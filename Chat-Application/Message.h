#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QString>
#include <qplaintextedit.h>
#include "Data.h"
#include "MsgStatus.h"

using namespace std;

namespace Ui {
class Message;
}

class Message: public QWidget {
    Q_OBJECT

public:
    explicit Message(QWidget *parent = nullptr);
    ~Message();

    void setUserData(QString userName, int colorIndex);
    int getColorsCount();
    void setMessage(QString s, bool SentByMe, bool isGroupChat);
    void ConvertFormat(QString &str);
    void getMessageInfo(QString messageID);
    void deleteMessage(QString messageID);
private slots:


private:
    MsgStatus *myMsgStatus  = new MsgStatus();;
    Data db;
    vector<QString> colors = {"rgb(68, 184, 172)", "rgb(91, 94, 166)", "rgb(188, 36, 60)", "rgb(128, 0, 85)"};
    Ui::Message *ui;
};

#endif // MESSAGE_H
