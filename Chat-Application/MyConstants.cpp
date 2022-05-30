#include "MyConstants.h"

 QString MyConstants::myId = "1";
 QString MyConstants::myName = "";
 QString MyConstants::myChatRoomName = "";
 QString MyConstants::myChatRoomID = "1";
 QString MyConstants::myChatRoomPic = "";
 QString MyConstants::myMsgID = "";

QString MyConstants::getMyId()
{
    return myId;
}

void MyConstants::setMyId( QString newMyId)
{
    myId = newMyId;
}

QString MyConstants::getMyName()
{
    return myName;
}

void MyConstants::setMyName( QString newMyName)
{
    myName = newMyName;
}

QString MyConstants::getMyChatRoomID()
{
    return myChatRoomID;
}

void MyConstants::setMyChatRoomID( QString newMyChatRoomID)
{
    myChatRoomID = newMyChatRoomID;
}

QString MyConstants::getMyChatRoomName()
{
    return myChatRoomName;
}

void MyConstants::setMyChatRoomName( QString newMyChatRoomName)
{
    myChatRoomName = newMyChatRoomName;
}

QString MyConstants::getMyMsgID()
{
    return myMsgID;
}

void MyConstants::setMyMsgID( QString newMyMsgID)
{
    myMsgID = newMyMsgID;
}

QString MyConstants::getMyChatRoomPic()
{
    return myChatRoomPic;
}

void MyConstants::setMyChatRoomPic(QString newMyChatRoomPic)
{
    myChatRoomPic = newMyChatRoomPic;
}

MyConstants::MyConstants() {


}
