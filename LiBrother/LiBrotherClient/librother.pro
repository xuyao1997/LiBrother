#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T16:59:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = librother
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    signup.cpp \
    signupmain.cpp \
    usermain.cpp

HEADERS  += mainwindow.h \
    login.h \
    signup.h \
    signupmain.h \
    usermain.h

FORMS    += mainwindow.ui \
    login.ui \
    signup.ui \
    signupmain.ui \
    usermain.ui