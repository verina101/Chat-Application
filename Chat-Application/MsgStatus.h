#ifndef MSGSTATUS_H
#define MSGSTATUS_H

#include <QDialog>

namespace Ui {
class MsgStatus;
}

class MsgStatus : public QDialog
{
    Q_OBJECT

public:
    explicit MsgStatus(QWidget *parent = nullptr);
    void setMsgStatus(QString date, QString time, bool isSeen);
    ~MsgStatus();

private:
    Ui::MsgStatus *ui;
};

#endif // MSGSTATUS_H
