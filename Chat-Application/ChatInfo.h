#ifndef CHATINFO_H
#define CHATINFO_H

#include <QWidget>

namespace Ui {
class ChatInfo;
}

class ChatInfo: public QWidget {
    Q_OBJECT

public:
    explicit ChatInfo(QWidget *parent = nullptr);
    ~ChatInfo();
    void setChatData(bool myChatType, QString myChatName, QString myDescription_admin, QString picture);

private:
    Ui::ChatInfo *ui;
};

#endif // CHATINFO_H
