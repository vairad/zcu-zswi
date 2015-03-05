#include "hlavni.h"
#include "ui_hlavni.h"
#include <QMessageBox>

Hlavni::Hlavni(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hlavni)
{
    ui->setupUi(this);
}

Hlavni::~Hlavni()
{
    delete ui;
}

void Hlavni::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Ukončit?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      QApplication::quit();
    }


}
