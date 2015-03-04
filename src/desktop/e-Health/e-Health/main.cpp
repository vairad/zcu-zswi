#include "hlavni.h"
#include <QtWidgets/QApplication>
#include <QPushButton>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Hlavni w;
	
	//QPushButton *k = w.ui.karel;
	//QObject::connect(w.ui.karel, SIGNAL(clicked()), &a, SLOT(quit())); // funguje! 

	//QObject::connect(w.ui.karel, SIGNAL(clicked()), &a, SLOT( zprava()));
	//QObject::connect(w.ui.karel, SIGNAL(clicked()), &a, SLOT(quit()));
	w.show();

	return a.exec();
}

