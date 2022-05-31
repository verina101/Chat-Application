#ifndef SHOWSTORIES_H
#define SHOWSTORIES_H

#include <QWidget>
#include <vector>
#include <string>
#include <saveddata.h>
#include <Data.h>
#include <StoryWidget.h>
#include <QListWidgetItem>

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
    vector<QString> storyIndex;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::ShowStories *ui;
    vector<vector<QString>> stories;
    bool isSelected = false;
};

#endif // SHOWSTORIES_H
