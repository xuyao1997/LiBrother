#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T16:59:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = librother
TEMPLATE = app
INCLUDEPATH += ../LiBrotherClientBackend/ \
../common/

CONFIG += C++11


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    signup.cpp \
    signupmain.cpp \
    usermain.cpp \
    bookdata.cpp \
    userborrow.cpp \
    announcement.cpp\
    manager.cpp\
    managermain.cpp \
    changepassword.cpp \
    addbook.cpp


HEADERS  += mainwindow.h \
    login.h \
    signup.h \
    signupmain.h \
    usermain.h \
    bookdata.h \
    userborrow.h\
    manager.h\
    announcement.h\
    managermain.h \
    changepassword.h \
    addbook.h


FORMS    += mainwindow.ui \
    login.ui \
    signup.ui \
    signupmain.ui \
    usermain.ui \
    bookdata.ui \
    userborrow.ui\
    announcement.ui\
    manager.ui\
    managermain.ui \
    changepassword.ui \
    addbook.ui


DISTFILES +=
