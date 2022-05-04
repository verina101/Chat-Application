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
    ChatRoom.cpp \
    Data.cpp \
    Message.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ChatInfo.h \
    ChatRoom.h \
    Data.h \
    Message.h \
    mainwindow.h

FORMS += \
    ChatInfo.ui \
    ChatRoom.ui \
    Message.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
