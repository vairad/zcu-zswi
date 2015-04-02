#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "MyThread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyThread *mThread;

private:
    Ui::MainWindow *ui;


private slots:
    void on_tlacitkoPripojit_clicked();
    void on_tlacitkoOdpojit_clicked();
    void on_tlacitkoHledejZarizeni_clicked();

public slots:

};

#endif // MAINWINDOW_H
