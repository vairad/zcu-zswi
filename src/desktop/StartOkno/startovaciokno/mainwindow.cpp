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
    connect(arduMiner,SIGNAL(ZmenaSpojeni(QString)),this,SLOT(on_ZmenaStavuSpojeni(QString)));
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
     ui->poleLog->append(stav);
}

void MainWindow::on_ZmenaStavuSpojeni(QString stavSpojeni) // pri zmene modelu nalezenych zarizeni
{
 ui->popisekStavSpojeni->setText(stavSpojeni);
     ui->poleLog->append(stavSpojeni);

}
void MainWindow::on_tlacitkoPripojit_clicked() // navázání spojení s vybraným zařízením
{
   /* ui->tlacitkoPripojit->setEnabled(false);
    arduMiner->ListNalezenychZarizeni.clear();
    this->modelNalezenychZarieni->setStringList(arduMiner->ListNalezenychZarizeni);
    ui->listView->setModel(this->modelNalezenychZarieni);*/

    arduMiner->stav = ArduinoMiner::STATUS_SPOJENI;
    arduMiner->start();
    ui->popisekStavSpojeni->setText("Připravuji spojení...");

    ui->poleLog->append("Připravuji spojení...");
}

void MainWindow::on_tlacitkoOdpojit_clicked()
{
    arduMiner->stav = ArduinoMiner::STATUS_KLID;
        ui->poleLog->append("Ukončuji spojení");
}

void MainWindow::on_tlacitkoHledejZarizeni_clicked()
{

    ui->tlacitkoPripojit->setEnabled(false); //tlačítko "Připojit" disabled
    arduMiner->ListNalezenychZarizeni.clear(); // vymazání seznamu nalezených zařízení
    this->modelNalezenychZarieni->setStringList(arduMiner->ListNalezenychZarizeni);// vymázání modelu
    ui->listView->setModel(this->modelNalezenychZarieni); // nastavení prázdného modelu do listView

    ui->poleLog->append("Začáním hledat");
    arduMiner->stav = ArduinoMiner::STATUS_HLEDEJ;
    arduMiner->start();
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->tlacitkoPripojit->setEnabled(true);
    QString zarizeniZeSeznamu = index.data().toString();
    arduMiner->vybraneZarizeni = zarizeniZeSeznamu;
    // Aplikace ví, s jakým zařízením se spojit
}
