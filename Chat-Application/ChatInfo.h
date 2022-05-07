#ifndef CHATINFO_H
#define CHATINFO_H

#include <QWidget>

namespace Ui {
class ChatInfo;
}

class ChatInfo: public QWidget
{
    Q_OBJECT

public:
    explicit ChatInfo(QWidget *parent = nullptr);
    ~ChatInfo();

private:
    Ui::ChatInfo *ui;
};

#endif // CHATINFO_H
