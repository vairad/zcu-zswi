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
    loadfile.cpp \
    sensorwidget.cpp \
    sensorekg.cpp \
    sensorposition.cpp \
    sensoroxy.cpp \
    sensorgsr.cpp \
    sensorheartrate.cpp \
    sensortemp.cpp \
    idisplayable.cpp \
    metadialog.cpp

HEADERS  += mainwindow.h \
    loadfile.h \
    sensorwidget.h \
    idisplayable.h \
    sensorekg.h \
    sensorposition.h \
    sensoroxy.h \
    sensorgsr.h \
    sensorheartrate.h \
    sensortemp.h \
    metadialog.h

FORMS    += mainwindow.ui
