#include "hlavni.h"

Hlavni::Hlavni(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this); // inicializace user-interface
	QObject::connect(ui->karel, SIGNAL(clicked()), this, SLOT(bla())); // pøipojení funkce bla na tlaèítko karel

}

void Hlavni::bla()
{
	QMessageBox msgBox;
	msgBox.setText("Hello world!");
	msgBox.exec();
}

