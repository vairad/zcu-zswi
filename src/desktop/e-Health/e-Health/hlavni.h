#ifndef HLAVNI_H
#define HLAVNI_H

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_hlavni.h"

namespace Ui {
	class Hlavni;
}

class Hlavni : public QMainWindow
{
	Q_OBJECT

public:
	Hlavni(QWidget *parent = 0);

private slots: // slot na funkce
	void bla();

public:
	Ui::HlavniClass *ui;
};
#endif // HLAVNI_H
