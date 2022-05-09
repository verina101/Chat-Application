#ifndef SHOWCONTACTNAMESTORY_H
#define SHOWCONTACTNAMESTORY_H
#include<string>
#include <QWidget>
#include "saveddata.h"
#include "Data.h"
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

private:
    Ui::ShowContactNameStory *ui;
};

#endif // SHOWCONTACTNAMESTORY_H
