#ifndef SAVEDDATA_H
#define SAVEDDATA_H
#include<string>
using namespace std;
class SavedData
{

    static string userId;
    static string userName;
    static string stortUserId;

public:

   SavedData();

   static void   setUserId(string id);
   static void   setUserName(string name);
   static string getUserId();
   static string getUserName();
   static void   setStoryUserID(string id);
   static string getStoryUserID();
};

#endif // SAVEDDATA_H
