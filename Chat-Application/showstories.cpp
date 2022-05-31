#include "showstories.h"
#include "ui_showstories.h"
#include <string>
#include <StoryTime.h>
#include <saveddata.h>
#include <ShowContactNameStory.h>
#include <MyConstants.h>
#include<iostream>
using namespace std;
ShowStories::ShowStories(QWidget *parent): QWidget(parent), ui(new Ui::ShowStories) {


    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));
    //background
    QPixmap myBackGround(":/images/assets/app_BackGround.jpg");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);

    SavedData contactId;
    Data MyDataBase;
    MyConstants myID;

    string id=contactId.getStoryUserID();
    string id2= myID.getMyId().toStdString();
    if(id==id2)
        ui->pushButton_3->setHidden(false);
    else
        ui->pushButton_3->setHidden(true);
    string col="*";
    string tableName="STORY";
    string cond= "where StoryOwnerID ='"+id+"' ;";
    this->stories = MyDataBase.SelectData(tableName,col,cond);
    for(auto it: this->stories){
        string time = it[5].toStdString();
        DateTime t;
        if(!t.isValidStory(time)){
            cond="where StoryID ='"+it[0].toStdString()+"' ;";
            MyDataBase.DeleteData(tableName,cond);
        }
        else{
            if(id==id2)
                storyIndex.push_back(it[0]);
            StoryWidget *mycontact = new StoryWidget();
            mycontact->setStoryData(it[2],"ID: "+ it[1], it[5]);
            int w = mycontact->width();
            int h = mycontact->height();
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            item->setSizeHint(QSize(w, h));
            ui->listWidget->setItemWidget(item, mycontact);
        }
    }

}




ShowStories::~ShowStories() {
    delete ui;
}

void ShowStories::on_pushButton_clicked() {
    ShowContactNameStory *s= new ShowContactNameStory();
    s->show();
    this->hide();
    ui->pushButton_3->setHidden(true);
  //  SavedData::setshowDeleteButton(false);
}


void ShowStories::on_pushButton_2_clicked()
{
    if(!this->isSelected) return;
    SavedData save;
    int indx = ui->listWidget->selectionModel()->currentIndex().row();
    string chosen = this->stories[indx][0].toStdString();
    save.setChosenStoryId(chosen);
    StoryTime *st= new StoryTime();
    st->show();
    this->hide();
    this->isSelected = false;

}


void ShowStories::on_pushButton_3_clicked()
{

    if(!this->isSelected) return;

    Data MyDataBase;
    string tableName="STORY";


    //cout<<"size"<< storyIndex.size();

    int indx = ui->listWidget->selectionModel()->currentIndex().row();
    string cond="where StoryID ='"+storyIndex[indx].toStdString()+"' ;";
    ui->listWidget->item(ui->listWidget->currentRow())->setHidden(true);
    MyDataBase.DeleteData(tableName,cond);
    this->isSelected = false;


}


void ShowStories::on_listWidget_itemClicked(QListWidgetItem *item)
{

    item->isHidden();
    this->isSelected = true;

}

