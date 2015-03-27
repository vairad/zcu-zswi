#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "graph.h"
#include "loadfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void draw();
    void thread();
    void addThread(LoadFile t);
    ~MainWindow();


private slots:
    void on_actionEKG_toggled(bool arg1);
    void on_actionTeplota_toggled(bool arg1);
    void on_actionZav_t_triggered();
    void on_actionO_aplikaci_triggered();

    void on_pushButton_clicked();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Graph *g;
    //QThread *t;



};

#endif // MAINWINDOW_H
