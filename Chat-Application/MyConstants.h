#ifndef MYCONSTANTS_H
#define MYCONSTANTS_H

#include <iostream>
#include <QString>
using namespace std;



class MyConstants {
    static QString myId;
    static QString myName;
    static QString myChatRoomID;
    static QString myChatRoomName;
    static QString myChatRoomPic;
    static QString myMsgID;

public:
    MyConstants();

    static  QString getMyId();
    static void setMyId( QString newMyId);
    static  QString getMyName();
    static void setMyName( QString newMyName);
    static  QString getMyChatRoomID();
    static void setMyChatRoomID( QString newMyChatRoomID);
    static  QString getMyChatRoomName();
    static void setMyChatRoomName( QString newMyChatRoomName);
    static  QString getMyMsgID();
    static void setMyMsgID( QString newMyMsgID);
    static  QString getMyChatRoomPic();
    static void setMyChatRoomPic( QString newMyChatRoomPic);
};

#endif // MYCONSTANTS_H
