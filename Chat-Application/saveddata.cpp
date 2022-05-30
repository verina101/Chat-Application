#include "saveddata.h"

SavedData::SavedData()
{


}
string SavedData::userId          ="1";
string SavedData::userName        ="";
string SavedData::storyUserId     ="3";
string SavedData::ChosenStoryId   ="";
bool   SavedData::showDeleteButton = false;
void SavedData::setUserId(string id){
    userId=id;
}

void SavedData::setUserName(string name){
    userName=name;
}

string SavedData::getUserId(){
    return userId;
}

string SavedData::getUserName(){
    return userName;
}

void SavedData::setStoryUserID(string i){
    storyUserId=i;
}

string SavedData::getStoryUserID(){
    return storyUserId;
}

void SavedData::setChosenStoryId(string i){
    ChosenStoryId=i;
}

string SavedData::getChosenStoryId(){
    return ChosenStoryId;
}


void SavedData::setshowDeleteButton(bool i){
    showDeleteButton=i;
}

bool SavedData::getshowDeleteButton(){
    return showDeleteButton;
}
