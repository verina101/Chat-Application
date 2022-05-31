#include "Chats.h"
#include "MyConstants.h"
#include "showcontactnamestory.h"
#include "ui_showcontactnamestory.h"
#include<iostream>
#include<QPixmap>
#include <ContactWidget.h>
#include <QMessageBox>
using namespace std;
ShowContactNameStory::ShowContactNameStory(QWidget *parent): QWidget(parent), ui(new Ui::ShowContactNameStory) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));


    //background
    QPixmap myBackGround(":/images/assets/app_BackGround.jpg");
    myBackGround = myBackGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(backgroundRole(), myBackGround);
    this->setPalette(palette);
    SavedData s;
    Data MyDataBase;

    //********************************
    // Delete old stories feom database
    //********************************
    vector<vector<QString>>vec;
    string tableName="STORY";
    string cond=";";
    string col="*";
    vec=MyDataBase.SelectData(tableName,col,cond);
    for(auto it : vec){
        string time = it[5].toStdString();
        DateTime t;
        if(!t.isValidStory(time)){
            cond="where StoryID ='"+it[0].toStdString()+"' ;";
            MyDataBase.DeleteData(tableName,cond);
        }
    }

    this->storyUsersID.clear();
    vector<vector<QString>>usersIds,checkvec;

    string contactCol       =  "ContactID";
    string contactTable     =  "CONTACTS" ;
    string contactCond      =  "where UserID = "+MyDataBase.convertToValue( MyConstants::getMyId()) + " ;";

    usersIds= MyDataBase.SelectData(contactTable,contactCol,contactCond); // [0] contacat id
    usersIds.push_back({MyConstants::getMyId()});


    for(int i =usersIds.size()-1;i >=0;i--){
        string id=usersIds[i][0].toStdString();
        string contactCol       =  "*";
        string contactTable     =  "STORY" ;
        string contactCond      =  "where StoryOwnerID ='"+id+"' ;";
        checkvec = MyDataBase.SelectData(contactTable,contactCol,contactCond);
        if(checkvec.size()){
            ContactWidget *mycontact = new ContactWidget();
            QString userPicture = MyDataBase.SelectData("USER","ProfilePicture","WHERE UserID = '" +id + "'").front().front();
            mycontact->setContactData(userPicture, checkvec[0][2], "ID: "+checkvec[0][1]);
            int w = mycontact->width();
            int h = mycontact->height();
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            item->setSizeHint(QSize(w, h));
            ui->listWidget->setItemWidget(item, mycontact);

            vector<QString>vec;
            vec.push_back(checkvec[0][1]);
            vec.push_back(checkvec[0][2]);
            storyUsersID.push_back(vec);
            vec.clear();
        }
        checkvec.clear();
    }

}
ShowContactNameStory::~ShowContactNameStory()
{
    delete ui;
}

void ShowContactNameStory::on_ShowStories_clicked()
{
    SavedData saved;

    int indx = ui->listWidget->selectionModel()->currentIndex().row();

    if(indx == -1){
        QMessageBox::warning(this,"View Story","No contact selected");
        return;
    }

    string s=storyUsersID[indx][0].toStdString();
    saved.setStoryUserID(s);
    ShowStories *ss= new ShowStories();
    ss->show();
    this->hide();
}


void ShowContactNameStory::on_Back_clicked()
{
    Chats *myChats = new Chats();
    myChats->show();
    this->close();
}


void ShowContactNameStory::on_pushButton_clicked()
{

    SavedData::setshowDeleteButton(true);
    ShowStories *ss= new ShowStories();
    ss->show();
    this->hide();

}

