#ifndef STORYWIDGET_H
#define STORYWIDGET_H

#include <QWidget>

namespace Ui {
class StoryWidget;
}

class StoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StoryWidget(QWidget *parent = nullptr);
    void setStoryData(QString name , QString id, QString date);
    ~StoryWidget();


private:
    Ui::StoryWidget *ui;
};

#endif // STORYWIDGET_H
