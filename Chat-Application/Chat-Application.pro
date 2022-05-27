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
    constantdata.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    saveddata.cpp \
    showcontact.cpp \
    showcontactnamestory.cpp \
    showstories.cpp \
    tstclass.cpp


HEADERS += \
    ChatInfo.h \
    ChatItem.h \
    ChatRoom.h \
    Chats.h \
    Data.h \
    constantdata.h \
    login.h \
    mainwindow.h \
    saveddata.h \
    showcontact.h \
    showcontactnamestory.h \
    showstories.h \
    tstclass.h


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
    mainwindow.ui \
    profile.ui





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recources.qrc
