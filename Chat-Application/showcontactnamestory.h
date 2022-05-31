#ifndef SHOWCONTACTNAMESTORY_H
#define SHOWCONTACTNAMESTORY_H
#include<string>
#include <QWidget>
#include "saveddata.h"
#include "Data.h"
#include "Datetime.h"
#include "showstories.h"
#include <QListWidgetItem>
using namespace std;
namespace Ui {
class ShowContactNameStory;
}

class ShowContactNameStory : public QWidget
{
    Q_OBJECT
    vector<vector<QString>>storyUsersID;
public:
    explicit ShowContactNameStory(QWidget *parent = nullptr);
    ~ShowContactNameStory();

private slots:
    void on_ShowStories_clicked();

    void on_Back_clicked();

    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::ShowContactNameStory *ui;
    bool isSelected = false;
};

#endif // SHOWCONTACTNAMESTORY_H
