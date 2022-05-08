#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QString>
#include <qplaintextedit.h>
using namespace std;

namespace Ui {
class Message;
}

class Message: public QWidget {
    Q_OBJECT

public:
    explicit Message(QWidget *parent = nullptr);
    ~Message();
    void setMessage(QString s, bool SentByMe);
    void ConvertFormat(QString &str);

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:

    Ui::Message *ui;
};

#endif // MESSAGE_H
