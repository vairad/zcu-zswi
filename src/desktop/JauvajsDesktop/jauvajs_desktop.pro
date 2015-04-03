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
    loadfile.cpp \
    core/idisplayable.cpp \
    core/sensorekg.cpp \
    core/sensorgsr.cpp \
    core/sensorheartrate.cpp \
    core/sensoroxy.cpp \
    core/sensorposition.cpp \
    core/sensortemp.cpp \
    gui/mainwindow.cpp \
    gui/metadialog.cpp \
    gui/sensorwidget.cpp \
    gui/detailedwindow.cpp \
    analysis/analyserekg.cpp \
    analysis/transcriberekg.cpp

HEADERS  += main.h\
    loadfile.h \
    core/idisplayable.h \
    core/sensorekg.h \
    core/sensorgsr.h \
    core/sensorheartrate.h \
    core/sensoroxy.h \
    core/sensorposition.h \
    core/sensortemp.h \
    gui/mainwindow.h \
    gui/metadialog.h \
    gui/sensorwidget.h \
    gui/ui_mainwindow.h \
    core/idatalistener.h \
    core/ianalyseable.h \
    core/iminer.h \
    gui/detailedwindow.h \
    analysis/analyserekg.h \
    analysis/transcriberekg.h

FORMS    += gui/mainwindow.ui