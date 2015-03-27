#-------------------------------------------------
#
# Project created by QtCreator 2015-03-17T19:15:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_arduino
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    loadfile.cpp

HEADERS  += mainwindow.h \
    graph.h \
    loadfile.h

FORMS    += mainwindow.ui
