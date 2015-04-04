#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "ArduinoMiner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ArduinoMiner *arduMiner;

private:
    Ui::MainWindow *ui;
    QStringListModel* modelNalezenychZarieni;

private slots:
    void on_tlacitkoPripojit_clicked();
    void on_tlacitkoOdpojit_clicked();
    void on_tlacitkoHledejZarizeni_clicked();

    void on_listView_clicked(const QModelIndex &index);

public slots:
    void on_SeznamChanged(QStringList* list);
    void on_ZmenaStavu(QString stav);
    void on_ZmenaStavuSpojeni(QString stavSpojeni);
};

#endif // MAINWINDOW_H
