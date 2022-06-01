#include "Chats.h"
#include "StoryTime.h"
#include "ui_StoryTime.h"
#include <saveddata.h>
#include <Data.h>
#include <showstories.h>
#include <QResource>

StoryTime::StoryTime(QWidget *parent): QWidget(parent), ui(new Ui::StoryTime) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    SavedData savee;
    Data MyData;
    string chosenn= savee.getChosenStoryId();
    string col="*";
    string tableName="STORY";
    string cond= "where StoryID ='"+chosenn+"' ;";
    vector<vector<QString>> chosenStory = MyData.SelectData(tableName, col, cond);

    if(chosenStory[0][4]=='0') {
        ui->label->setText(chosenStory[0][3]);
    }
    else{

        string path= chosenStory[0][4].toStdString(),name="";

        for(int i=path.size() - 1; i>-1; --i){
            if(path[i] == '/') break;

            name = path[i] + name;
        }


        QPixmap photo(QString::fromStdString(path));
        int h= ui->label->height();
        int w= ui->label->width();
        ui->label-> setPixmap(photo.scaled(w,h, Qt::IgnoreAspectRatio));
    }


}


StoryTime::~StoryTime() {
    delete ui;
}


void StoryTime::on_pushButton_clicked()
{
    ShowStories *s= new ShowStories();
    s->show();
    this->hide();
}


void StoryTime::on_pushButton_2_clicked()
{
    Chats *myChats = new Chats();
    myChats->show();
    this->close();
}
