#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>

namespace Ui {
class ChatItem;
}

class ChatItem : public QWidget {
    Q_OBJECT

public:
    explicit ChatItem(QWidget *parent = nullptr);
    ~ChatItem();

    void setChatData(QString chatPhoto, QString chatName, QString msgSender ,QString msg);

private:
    Ui::ChatItem *ui;
};

#endif // CHATITEM_H
