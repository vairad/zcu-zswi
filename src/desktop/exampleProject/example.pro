#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T13:55:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = e-Health
TEMPLATE = app


SOURCES += main.cpp\
        hlavni.cpp \
    bluetooth.cpp \
    bt/bluetooth.cpp

HEADERS  += hlavni.h \
    bt/bluetooth.h

FORMS    += hlavni.ui
