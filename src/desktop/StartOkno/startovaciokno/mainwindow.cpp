#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ArduinoMiner.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->modelNalezenychZarieni = new QStringListModel();
    arduMiner = new ArduinoMiner(this);
    connect(arduMiner,SIGNAL(SeznamChanged(QStringList*)),this,SLOT(on_SeznamChanged(QStringList*)));
    connect(arduMiner,SIGNAL(ZmenaStavu(QString)),this,SLOT(on_ZmenaStavu(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SeznamChanged(QStringList *list) // pri zmene modelu nalezenych zarizeni
{
 this->modelNalezenychZarieni->setStringList(*list);// poslani prvniho zarizeni do listu
 ui->listView->setModel(this->modelNalezenychZarieni);
}

void MainWindow::on_ZmenaStavu(QString stav) // pri zmene modelu nalezenych zarizeni
{
 ui->popisekStav->setText(stav);

}

void MainWindow::on_tlacitkoPripojit_clicked()
{

}

void MainWindow::on_tlacitkoOdpojit_clicked()
{

}

void MainWindow::on_tlacitkoHledejZarizeni_clicked()
{
    ui->tlacitkoPripojit->setEnabled(false); //tlačítko "Připojit" disabled
    arduMiner->ListNalezenychZarizeni.clear(); // vymazání seznamu nalezených zařízení
    this->modelNalezenychZarieni->setStringList(arduMiner->ListNalezenychZarizeni);// vymázání modelu
    ui->listView->setModel(this->modelNalezenychZarieni); // nastavení prázdného modelu do listView

    arduMiner->start();
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->tlacitkoPripojit->setEnabled(true);
    /*QMessageBox msgBox;
    msgBox.setText("Vybrano: "+index);
    msgBox.exec();
    /*
    int row=index.row();
    testlabel->setText(index.sibling(row,1).data(Qt::DisplayRole).toString());*/
}
