#-------------------------------------------------
#
# Project created by QtCreator 2015-03-17T19:15:04
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sejdrem_sensor
TEMPLATE = app

CONFIG += c++11

win32{
    LIBS += -lWS2_32
    LIBS += -lBTHPROPS

    DEFINES += WIN32_LEAN_AND_MEAN
}

SOURCES += main.cpp\
    core/idisplayable.cpp \
    core/sensorekg.cpp \
    core/sensorheartrate.cpp \
    core/sensoroxy.cpp \
    core/sensortemp.cpp \
    gui/mainwindow.cpp \
    gui/metadialog.cpp \
    gui/sensorwidget.cpp \
    gui/detailedwindow.cpp \
    analysis/analyserekg.cpp \
    analysis/transcriberekg.cpp \
    gui/graphdescription.cpp \
    core/datamanager.cpp \
    core/filesaver.cpp \
    core/fileminer.cpp \
    core/arduinominer.cpp \
    core/metadatareader.cpp \
    gui/initialwindow.cpp \
    gui/analysiswindow.cpp \
    gui/connectionwindow.cpp \
    core/fileproblemexception.cpp \
    core/sensorairflow.cpp \
    gui/helpwindow.cpp \
    core/sensorconductance.cpp \
    core/sensorresistance.cpp

HEADERS  += core/idisplayable.h \
    core/sensorekg.h \
    core/sensorheartrate.h \
    core/sensoroxy.h \
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
    analysis/transcriberekg.h \
    gui/graphdescription.h \
    core/datamanager.h \
    core/istorable.h \
    core/filesaver.h \
    core/fileminer.h \
    core/arduinominer.h \
    core/iworking.h \
    core/metadatareader.h \
    gui/initialwindow.h \
    gui/analysiswindow.h \
    core/fileproblemexception.h \
    gui/connectionwindow.h \
    core/sensorairflow.h \
    gui/helpwindow.h \
    core/sensorresistance.h \
    core/sensorconductance.h

FORMS    += gui/mainwindow.ui
RC_FILE = myapp.rc
