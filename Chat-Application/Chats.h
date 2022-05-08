#ifndef CHATS_H
#define CHATS_H

#include "Data.h"
#include "QMap"
#include <QWidget>

namespace Ui {
class Chats;
}

class Chats : public QWidget {
    Q_OBJECT

public:
    explicit Chats(QWidget *parent = nullptr);
    ~Chats();

private slots:
    void on_pushButton_createChat_clicked();

private:
    Ui::Chats *ui;
    void displayChatList();
    Data db;
};

#endif // CHATS_H
