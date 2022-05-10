#include "showcontactnamestory.h"
#include "ui_showcontactnamestory.h"
#include<iostream>
using namespace std;
ShowContactNameStory::ShowContactNameStory(QWidget *parent): QWidget(parent), ui(new Ui::ShowContactNameStory) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(700, 500));
    this->setMaximumSize(QSize(700, 500));
    //********************************
    // Delte old stories feom database
    //********************************
    SavedData s;
    Data MyDataBase;
    this->storyUsersID.clear();
    vector<vector<QString>>usersIds,checkvec;

    string contactCol       =  "ContactID";
    string contactTable     =  "CONTACTS" ;
    string contactCond      =  "where UserID ='"+s.getUserId()+"' ;";
    usersIds= MyDataBase.SelectData(contactTable,contactCol,contactCond); // [0] contacat id




    for(int i =0;i < usersIds.size();i++){
        string id=usersIds[i][0].toStdString();
        string contactCol       =  "*";
        string contactTable     =  "STORY" ;
        string contactCond      =  "where StoryOwnerID ='"+id+"' ;";
        checkvec = MyDataBase.SelectData(contactTable,contactCol,contactCond);
        if(checkvec.size()){
            ui->listWidget->addItem("\n" + checkvec[0][2] +"\n"+"ID : "+ checkvec[0][1]+"\n") ;
            vector<QString>vec;
            vec.push_back(checkvec[0][1]);
            vec.push_back(checkvec[0][2]);
            storyUsersID.push_back(vec);
            vec.clear();
        }
        checkvec.clear();
    }


//    this->data= MyDataBase.SelectData(userTable,userCol,userCond);
//     cout<< "size is "<< data.size();

    cout<<"sizee " << storyUsersID.size();
    for (auto it : storyUsersID) {
            for (auto itt : it) {
                qDebug() << "curr user id"<< itt<< "\n";
            }
            cout << "\n";
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
    string s=storyUsersID[indx][0].toStdString();
    saved.setStoryUserID(s);
    cout<<storyUsersID[indx][0].toStdString()<<endl;
    cout<<"Story user id   "<<saved.getStoryUserID()<<endl;
}

