QT       += core sql
QT       += core gui
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChatInfo.cpp \
    ChatItem.cpp \
    ChatRoom.cpp \
    Chats.cpp \
    Data.cpp \
    Datetime.cpp \
    Message.cpp \
    MsgStatus.cpp \
    MyConstants.cpp \
    StoryTime.cpp \
    StoryWidgett.cpp \
    main.cpp \
    login.cpp \
    addstory.cpp \
    contact.cpp \
    contactwidget.cpp \
    saveddata.cpp \
    showcontact.cpp \
    showcontactnamestory.cpp \
    showstories.cpp \
    profile.cpp \
    constantdata.cpp



HEADERS += \
    ChatInfo.h \
    ChatItem.h \
    ChatRoom.h \
    Chats.h \
    Data.h \
    Datetime.h \
    Message.h \
    MsgStatus.h \
    MyConstants.h \
    StoryTime.h \
    StoryWidget.h \
    login.h \
    addstory.h \
    contact.h \
    contactwidget.h \
    saveddata.h \
    showcontact.h \
    showcontactnamestory.h \
    showstories.h \
    profile.h \
    constantdata.h



FORMS += \
    ChatInfo.ui \
    ChatItem.ui \
    ChatRoom.ui \
    Chats.ui \
    Message.ui \
    MsgStatus.ui \
    StoryTime.ui \
    StoryWidget.ui \
    login.ui \
    addstory.ui \
    contact.ui \
    contactwidget.ui \
    showcontact.ui \
    showcontactnamestory.ui \
    showstories.ui \
    profile.ui




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recources.qrc

