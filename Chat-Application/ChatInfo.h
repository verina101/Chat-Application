#ifndef CHATINFO_H
#define CHATINFO_H

#include "Data.h"
#include "MyConstants.h"

#include <QWidget>

namespace Ui {
class ChatInfo;
}

class ChatInfo: public QWidget {
    Q_OBJECT

public:
    explicit ChatInfo(QWidget *parent = nullptr);
    ~ChatInfo();
    void setChatData();

private:
    Ui::ChatInfo *ui;
    Data db;
};

#endif // CHATINFO_H
