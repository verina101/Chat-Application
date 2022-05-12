#include "MyConstants.h"

 QString MyConstants::myId = "";
 QString MyConstants::myName = "";
 QString MyConstants::myChatRoomName = "";
 QString MyConstants::myChatRoomID = "";
 QString MyConstants::myChatRoomType = "";

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

 QString MyConstants::getMyChatRoomType()
{
    return myChatRoomType;
}

void MyConstants::setMyChatRoomType( QString newMyChatRoomType)
{
    myChatRoomType = newMyChatRoomType;
}

MyConstants::MyConstants() {


}
