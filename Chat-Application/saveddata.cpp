#include "saveddata.h"

SavedData::SavedData()
{


}
string SavedData::userId      ="1";
string SavedData::userName    ="";
string SavedData::stortUserId ="";
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
    stortUserId=i;
}

string SavedData::getStoryUserID(){
    return stortUserId;
}


