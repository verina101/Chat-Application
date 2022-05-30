#ifndef SAVEDDATA_H
#define SAVEDDATA_H
#include<string>
using namespace std;
class SavedData
{

    static string userId;
    static string userName;
    static string storyUserId;
    static string ChosenStoryId;
    static bool   showDeleteButton;

public:

    SavedData();

    static void   setUserId(string id);
    static void   setUserName(string name);
    static string getUserId();
    static string getUserName();
    static void   setStoryUserID(string id);
    static string getStoryUserID();
    static void   setChosenStoryId(string id);
    static string getChosenStoryId();
    static void   setshowDeleteButton(bool i);
    static bool getshowDeleteButton();

};

#endif // SAVEDDATA_H
