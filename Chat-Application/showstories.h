#ifndef SHOWSTORIES_H
#define SHOWSTORIES_H

#include <QWidget>
#include <vector>
#include <string>
#include <saveddata.h>
#include <Data.h>
#include <StoryWidget.h>
using namespace std;

namespace Ui {
class ShowStories;
}

class ShowStories : public QWidget
{
    Q_OBJECT

public:
    explicit ShowStories(QWidget *parent = nullptr);
    ~ShowStories();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ShowStories *ui;
    vector<vector<QString>> stories;
};

#endif // SHOWSTORIES_H
