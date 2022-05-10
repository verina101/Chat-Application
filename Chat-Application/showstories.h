#ifndef SHOWSTORIES_H
#define SHOWSTORIES_H

#include <QWidget>

namespace Ui {
class ShowStories;
}

class ShowStories : public QWidget
{
    Q_OBJECT

public:
    explicit ShowStories(QWidget *parent = nullptr);
    ~ShowStories();

private:
    Ui::ShowStories *ui;
};

#endif // SHOWSTORIES_H
