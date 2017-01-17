#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T16:48:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimerManager
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    hal.cpp \
    timman.cpp

HEADERS  += mainwindow.h \
    hal.h \
    timman.h

FORMS    += mainwindow.ui
