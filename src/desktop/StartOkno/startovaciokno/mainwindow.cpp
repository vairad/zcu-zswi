#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ArduinoMiner.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->modelNalezenychZarieni = new QStringListModel();
    arduMiner = new ArduinoMiner(this);

    connect(arduMiner,SIGNAL(ListChanged(QStringList*)),this,SLOT(on_SeznamChanged(QStringList*)));
    connect(arduMiner,SIGNAL(changeStatus(QString)),this,SLOT(on_ZmenaStavu(QString)));
    connect(arduMiner,SIGNAL(ConnectionChanged(QString)),this,SLOT(on_ZmenaStavuSpojeni(QString)));
    connect(arduMiner,SIGNAL(ReceiveData(QString)),this,SLOT(on_PrijmiData(QString)));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_SeznamChanged(QStringList *list){ // pri zmene modelu nalezenych zarizeni

 this->modelNalezenychZarieni->setStringList(*list);// poslani prvniho zarizeni do listu
 ui->listView->setModel(this->modelNalezenychZarieni);
}

void MainWindow::on_ZmenaStavu(QString stav){ // pri zmene modelu nalezenych zarizeni

  ui->popisekStav->setText(stav);
  ui->poleLog->append(stav);
}

void MainWindow::on_ZmenaStavuSpojeni(QString stavSpojeni){ // pri zmene modelu nalezenych zarizeni

  ui->popisekStavSpojeni->setText(stavSpojeni);
  ui->poleLog->append(stavSpojeni);

}
void MainWindow::on_tlacitkoPripojit_clicked(){ // navázání spojení s vybraným zařízením

    arduMiner->stav = ArduinoMiner::STATUS_SPOJENI;
    arduMiner->start();
    ui->popisekStavSpojeni->setText("Připravuji spojení k "+arduMiner->vybraneZarizeni);

    ui->poleLog->append("Připravuji spojení k "+arduMiner->vybraneZarizeni);
}

void MainWindow::on_tlacitkoOdpojit_clicked(){
    ui->poleLog->append("Ukončuji spojení");
    arduMiner->CloseConnection();
}

void MainWindow::on_tlacitkoHledejZarizeni_clicked(){
    ui->tlacitkoPripojit->setEnabled(false); //tlačítko "Připojit" disabled
    arduMiner->ListFoundDevices.clear(); // vymazání seznamu nalezených zařízení
    this->modelNalezenychZarieni->setStringList(arduMiner->ListFoundDevices);// vymázání modelu
    ui->listView->setModel(this->modelNalezenychZarieni); // nastavení prázdného modelu do listView

    ui->poleLog->append("Začáním hledat");
    arduMiner->stav = ArduinoMiner::STATUS_HLEDEJ;
    arduMiner->start();
}

void MainWindow::on_listView_clicked(const QModelIndex &index){
    ui->tlacitkoPripojit->setEnabled(true);
    QString zarizeniZeSeznamu = index.data().toString();
    arduMiner->vybraneZarizeni = zarizeniZeSeznamu;
    // Aplikace ví, s jakým zařízením se spojit
}

void MainWindow::on_PrijmiData(QString data){
    ui->polePrijataData->append(data);
}

void MainWindow::on_tlacitkoOdeslat_clicked(){
    QString obsah = ui->poleKOdeslani->text();
    if(obsah != ""){
        arduMiner->SendData(obsah);
        ui->poleKOdeslani->setText("");
    }
}
