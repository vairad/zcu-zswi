#include "initialwindow.h"
#include <QApplication>
#include <QButtonGroup>

/**
 * Vytvori uvodni okno
 * @brief InitialWindow::InitialWindow
 * @param dataManager spravce dat
 * @param parent
 */
InitialWindow::InitialWindow(DataManager *dataManager, QWidget *parent) : QDialog(parent), dataManager(dataManager) {
    this->resize(501, 313);

    setWindowTitle("Vítejte v aplikaci E-health");

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(20, 20, 20, 20);

    createTitle();
    createListOfNames();
    createButtons();

    QMetaObject::connectSlotsByName(this);
}

/**
 * Vytvori uvodni nadpis
 * @brief InitialWindow::createTitle
 */
void InitialWindow::createTitle() {
    QLabel *label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setMaximumSize(QSize(16777215, 20));
    QFont font;
    font.setFamily(QStringLiteral("Calibri"));
    font.setPointSize(16);
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);
    label->setText("Vítejte v aplikaci E-health");

    verticalLayout->addWidget(label);
}

/**
 * Vypise jmena ulozenych uzivatelu
 * @brief InitialWindow::createListOfNames
 */
void InitialWindow::createListOfNames() {
    // widget pro vypis uzivatelu
    QWidget *widget = new QWidget(this);
    widget->setObjectName(QStringLiteral("widget"));
    QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
    widgetLayout->setAlignment(Qt::AlignTop);

    // ziska list uzivatelskych jmen v datove slozce
    QStringList list = dataManager->listOfFolders();
    QFont font1;
    font1.setUnderline(true);

    foreach (QString s, list) {
        QLabel *label = new QLabel(/*widget*/);
        label->setObjectName(QStringLiteral("label_2"));
        label->setGeometry(QRect(20, 20, 461, 13));
        label->setFont(font1);
        label->setCursor(Qt::PointingHandCursor);
        label->setText(dataManager->getNameFromMetadata(s));

        widgetLayout->addWidget(label);
    }

    verticalLayout->addWidget(widget);
}

/**
 * Vytvori tlacitka
 * @brief InitialWindow::createButtons
 */
void InitialWindow::createButtons() {
    QWidget *widgetBT = new QWidget();
    QHBoxLayout *group = new QHBoxLayout(widgetBT);

    // tlacitko vytvorit noveho uzivatele
    QPushButton *createBT = new QPushButton();
    createBT->setObjectName(QStringLiteral("button"));
    createBT->setGeometry(QRect(10, 50, 131, 23));
    createBT->setText("Vytvoř nového uživatele");
    group->addWidget(createBT);

    // tlacitko pokracovat bez prihlaseni
    QPushButton *continueBT = new QPushButton();
    continueBT->setObjectName(QStringLiteral("button_2"));
    continueBT->setGeometry(QRect(10, 50, 131, 23));
    continueBT->setText("Pokračuj bez přihlášení");
    group->addWidget(continueBT);

    verticalLayout->addWidget(widgetBT, 0, Qt::AlignBottom);
}

InitialWindow::~InitialWindow() {

}

