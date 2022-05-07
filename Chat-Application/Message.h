#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <string>

using namespace std;

namespace Ui {
class Message;
}

class Message: public QWidget
{
    Q_OBJECT

public:
    explicit Message(QWidget *parent = nullptr);
    ~Message();

    bool setMessage(QString s, bool SentByMe);
private:
    void ConvertFormat(QString &str);
    Ui::Message *ui;
};

#endif // MESSAGE_H
