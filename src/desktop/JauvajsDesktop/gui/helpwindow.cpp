#include <QPushButton>
#include <QFile>
#include <QTextStream>

#include "helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) : QDialog(parent) {
    this->resize(501, 313);

    setWindowTitle("Nápověda k aplikaci");

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setAlignment(Qt::AlignTop);
    createTextEdit();
    createButton();
    this->show();
}

/**
 * Vytvori pole pro zobrazeni napovedy
 * @brief HelpWindow::createTextEdit
 */
void HelpWindow::createTextEdit() {
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);


    QFile file("help/help.html");
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    if (!file.exists()) {
        textEdit->setText("Chybí soubor 'help/help.html'");
    }
    else {
        file.open (QIODevice::ReadOnly);

        textEdit->setHtml(stream.readAll());
        file.close(); // when your done.
    }

    verticalLayout->addWidget(textEdit);
}

/**
 * Vytvori tlacitko
 * @brief HelpWindow::createButtons
 */
void HelpWindow::createButton() {
    // tlacitko pro zavreni okna
    QPushButton *bt1 = new QPushButton();
    bt1->setText("Zavřít");
    bt1->setMaximumWidth(100);
    connect(bt1, SIGNAL(clicked()), this, SLOT(close()));
    verticalLayout->addWidget(bt1, 0, Qt::AlignRight);
}

HelpWindow::~HelpWindow() {

}

