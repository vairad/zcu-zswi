#include <QTextEdit>
#include <QPushButton>

#include "connectionwindow.h"
#include "core/arduinominer.h"

ConnectionWindow::ConnectionWindow(ArduinoMiner *arduinoMiner, QWidget *parent) : QDialog(parent) {
    this->arduinoMiner = arduinoMiner;
    this->resize(501, 313);

    setWindowTitle("Okno");

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(20, 20, 20, 20);
    verticalLayout->setAlignment(Qt::AlignTop);
    createTextEdit();
    createButtons();
    this->show();
}

void ConnectionWindow::createTextEdit() {
    textEdit = new QTextEdit;
    verticalLayout->addWidget(textEdit);
}

/**
 * Vytvori tlacitka
 * @brief InitialWindow::createButtons
 */
void ConnectionWindow::createButtons() {
    QWidget *widgetBT = new QWidget();
    QHBoxLayout *group = new QHBoxLayout(widgetBT);

    // tlacitko vytvorit noveho uzivatele
    QPushButton *bt1 = new QPushButton();
    bt1->setObjectName(QStringLiteral("button"));
    bt1->setText("Připojit");
    group->addWidget(bt1);
    connect(bt1, SIGNAL (clicked()), this, SLOT (connectArduino()));

    // tlacitko pro odpojeni
    QPushButton *bt2 = new QPushButton();
    bt2->setObjectName(QStringLiteral("button_2"));
    bt2->setText("Odpojit");
    group->addWidget(bt2);
    connect(bt2, SIGNAL (clicked()), this, SLOT (disconnectArduino()));

    verticalLayout->addWidget(widgetBT, 0, Qt::AlignBottom);
}

void ConnectionWindow::connectArduino() {
   this->arduinoMiner->init();
   this->arduinoMiner->navazSpojeni();
}

void ConnectionWindow::disconnectArduino() {
   this->arduinoMiner->UkonciSpojeni();
}

void ConnectionWindow::serialReceived(QString data) {
    this->textEdit->append(data);
}

ConnectionWindow::~ConnectionWindow() {

}

