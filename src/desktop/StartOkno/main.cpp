#include "mainwindow.h"
#include <QApplication>
#include "ui_mainwindow.h"

//////////////////////////

#include <Winsock2.h>
#include <Windows.h>
#include <BluetoothAPIs.h>
#include <Ws2bth.h>

///////////////////////////

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ///////////////

   /* ArduinoMiner* arduinoMiner = new ArduinoMiner();
    arduinoMiner->start();*/
    //MainWindow::ui->listView->setModel(arduinoMiner->modelNalezenychZarieni);


    ///////////////
    return a.exec();
}