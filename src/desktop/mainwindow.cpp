#include <QtWidgets>
#include "mainwindow.h"
#include "graph.h"

/**
  Vytvori okno
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    //scene->setSceneRect(QRectF(QPointF(0,0),QPointF(500,500)));
    ui->graphicsView->setScene(scene);
    //t = new LoadFile(g);
}

/**
 * Vytvoreni zkusebniho grafu
 * @brief MainWindow::draw
 */
void MainWindow::draw() {
    g = new Graph(ui->graphicsView);
}

MainWindow::~MainWindow() {
    delete ui;
}

/**
 * Zobrazeni nebo skryti grafu pro senzor
 * @brief MainWindow::on_actionEKG_toggled
 * @param arg1
 */
void MainWindow::on_actionEKG_toggled(bool arg1) {
    if (arg1) {
       ui->widget_1->show();
    }
    else {
       ui->widget_1->hide();
    }
}

/**
 * Zobrazeni nebo skryti grafu pro senzor
 * @brief MainWindow::on_actionTeplota_toggled
 * @param arg1
 */
void MainWindow::on_actionTeplota_toggled(bool arg1) {
    if (arg1) {
       ui->widget_2->show();
    }
    else {
       ui->widget_2->hide();
    }
}

/**
 * Zavre aplikaci
 * @brief MainWindow::on_actionZav_t_triggered
 */
void MainWindow::on_actionZav_t_triggered() {
    this->close();
}

/**
 * Zobrazi informace o aplikaci
 * @brief MainWindow::on_actionO_aplikaci_triggered
 */
void MainWindow::on_actionO_aplikaci_triggered() {
    QMessageBox::about(this, tr("O aplikaci"),
             tr("Aplikace pro vizualizaci signálů z E-health. <br> Projekt Šejdrem Arduino"));
}

/**
 * Stara se o spravnou velikost scene pri zmene velikosti okna
 * @brief MainWindow::resizeEvent
 * @param e
 */
void MainWindow::resizeEvent(QResizeEvent *e) {
    ui->graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QPointF(ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height())));
}

/**
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked() {
    new LoadFile(g);
}
