#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyThread.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tlacitkoPripojit_clicked()
{

}

void MainWindow::on_tlacitkoOdpojit_clicked()
{

}

void MainWindow::on_tlacitkoHledejZarizeni_clicked()
{
    MyThread* arduinoMiner = new MyThread();
    arduinoMiner->run();
    ui->listView->setModel(arduinoMiner->modelNalezenychZarieni);
}

