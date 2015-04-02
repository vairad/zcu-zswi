#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T12:15:23
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = includeKnihoven
TEMPLATE = app

@win32:
LIBS += -lWS2_32
LIBS += -lBTHPROPS
@

SOURCES += main.cpp\
        mainwindow.cpp \
    MyThread.cpp

HEADERS  += mainwindow.h \
    MyThread.h

FORMS    += mainwindow.ui
