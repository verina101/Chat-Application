#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>

using namespace std;
namespace Ui {
class Message;
}

class Message : public QWidget
{
    Q_OBJECT

public:
    explicit Message(QWidget *parent = nullptr);
    ~Message();
    void setMessageText(QString text, int lineCount);

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Message *ui;
};

#endif // MESSAGE_H
