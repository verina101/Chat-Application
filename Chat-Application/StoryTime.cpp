#include "Chats.h"
#include "StoryTime.h"
#include "ui_StoryTime.h"
#include <saveddata.h>
#include <Data.h>
#include <showstories.h>
StoryTime::StoryTime(QWidget *parent): QWidget(parent), ui(new Ui::StoryTime) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));

    //background
    QPixmap myBackGround(":/images/assets/app_BackGround.jpg");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);

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
       bool p=false;
       for(int i=path.size(); i>-1; --i){
           if(path[i]=='/')
               break;
           if(path[i]=='.'){
               p=true;
               continue;
       }
           if(p)
              name+=path[i];
       }

       reverse(name.begin(), name.end());

//        name=ConvertoValue(name);

        QPixmap photo(QString::fromStdString(path));
        int h= ui->label->height();
        int w= ui->label->width();
        ui->label-> setPixmap(photo.scaled(w,h, Qt::KeepAspectRatio));
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

