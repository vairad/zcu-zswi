#include "initialwindow.h"
#include <QApplication>
#include <QButtonGroup>
#include "mainwindow.h"

/**
 * Vytvori uvodni okno
 * @brief InitialWindow::InitialWindow
 * @param dataManager spravce dat
 * @param parent
 */
InitialWindow::InitialWindow(DataManager *dataManager, QWidget *parent) : QDialog(parent), dataManager(dataManager) {
    this->resize(501, 313);
    this->mainWindow = parent;

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
        UserLabel *label = new UserLabel(s);
        label->setObjectName(QStringLiteral("label_2"));
        label->setGeometry(QRect(20, 20, 461, 13));
        label->setFont(font1);
        label->setCursor(Qt::PointingHandCursor);
        label->setText(dataManager->getNameFromMetadata(s));

        widgetLayout->addWidget(label);
        // propojeni udalosti na kliknuti s setUser
        connect(label, SIGNAL(clicked(QString)), this, SLOT(setUser(QString)));
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
    // propojeni udalosti na kliknuti
    connect(createBT, SIGNAL(clicked()), this, SLOT(createNewUser()));

    // tlacitko pokracovat bez prihlaseni
    QPushButton *continueBT = new QPushButton();
    continueBT->setObjectName(QStringLiteral("button_2"));
    continueBT->setGeometry(QRect(10, 50, 131, 23));
    continueBT->setText("Pokračuj bez přihlášení");
    group->addWidget(continueBT);
    // propojeni udalosti na kliknuti
    connect(continueBT, SIGNAL(clicked()), this, SLOT(closeWithoutLogin()));

    verticalLayout->addWidget(widgetBT, 0, Qt::AlignBottom);
}

/**
 * Nastavi zvoleneho uzivatele
 * @brief InitialWindow::setUser
 * @param username uzivatelske jmeno
 */
void InitialWindow::setUser(QString username) {
    dataManager->getMetadata(username);
    ((MainWindow *)mainWindow)->setUp();
    this->hide();
}

/**
 * Zavre uvodni okno bez nastaveni metadat pouze jako promotion
 * @brief InitialWindow::closeWithoutLogin
 */
void InitialWindow::closeWithoutLogin() {
    dataManager->logoutUser();
    ((MainWindow *)mainWindow)->setUp();
    this->hide();
}

/**
 * Otevre dialog k vytvoreni noveho uzivatele a zavre uvodni okno
 * @brief InitialWindow::createNewUser
 */
void InitialWindow::createNewUser() {
    dataManager->logoutUser();
    ((MainWindow *)mainWindow)->setUp();
    ((MainWindow *)mainWindow)->metaDialog->show();
    this->hide();
}

/**
 * Reakce na zavreni okna krizkem
 * @brief InitialWindow::closeEvent
 */
void InitialWindow::closeEvent(QCloseEvent *) {
    closeWithoutLogin();
}

InitialWindow::~InitialWindow() {

}
/**
 * Vytvori uzivatelsky label
 * @brief UserLabel::UserLabel
 * @param parent
 */
UserLabel::UserLabel(QString username, QWidget *parent) : QLabel(parent), username(username) {}

/**
 * Reakce na stisk labelu vola signal clicked
 * @brief UserLabel::mousePressEvent
 * @param event
 */
void UserLabel::mousePressEvent(QMouseEvent *) {
    emit clicked(username);
}

UserLabel::~UserLabel() {}
