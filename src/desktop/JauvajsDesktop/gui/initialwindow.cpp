#include <QApplication>
#include <QButtonGroup>
#include <QtAlgorithms>

#include "initialwindow.h"
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
    createListOfNames2();
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

    // workspace radek
    QWidget *widgetWS = new QWidget();
    QHBoxLayout *group = new QHBoxLayout(widgetWS);

    // cesta k aktualnimu workspace
    QFileInfo pathInfo(dataManager->FOLDER_NAME);
    workspacePathE = new QLineEdit(pathInfo.absoluteFilePath());
    workspacePathE->setReadOnly(true);
    group->addWidget(workspacePathE);

    // tlacitko zmenit workspace
    QPushButton *selectBT = new QPushButton();
    selectBT->setObjectName(QStringLiteral("button"));
    selectBT->setGeometry(QRect(10, 50, 131, 23));
    selectBT->setText("Změnit workspace");
    group->addWidget(selectBT);
    // propojeni udalosti na kliknuti
    connect(selectBT, SIGNAL(clicked()), this, SLOT(changeWorkspace()));

    verticalLayout->addWidget(widgetWS, 0, Qt::AlignTop);
}

/**
 * Pripravi okno pro vypis ulozenych uzivatelu
 * @brief InitialWindow::createListOfNames
 */
void InitialWindow::createListOfNames() {
    // widget pro vypis uzivatelu
    QWidget *widget = new QWidget(this);
    widget->setObjectName(QStringLiteral("widget"));
    widgetLayout = new QVBoxLayout(widget);
    widgetLayout->setAlignment(Qt::AlignTop);

    listsOfNames();

    verticalLayout->addWidget(widget, 1, Qt::AlignTop);
}

/**
 * Vypise jmena vsech ulozenych uzivatelu
 * @brief InitialWindow::listsOfNames
 */
void InitialWindow::listsOfNames() {
    QString name;
    // indikuje, zda je ve slozce nejaka slozka s metadata.txt
    bool isExistName = false;
    // ziska list uzivatelskych jmen v datove slozce
    QStringList list = dataManager->listOfFolders();
    QFont font1;
    font1.setUnderline(true);

    foreach (QString s, list) {
        name = dataManager->getNameFromMetadata(s);
        if (!name.isNull()) {
            isExistName = true;
            UserLabel *label = new UserLabel(s, dataManager->getDateTimeFromMetadata(s));
            label->setObjectName(QStringLiteral("label_2"));
            label->setGeometry(QRect(20, 20, 461, 13));
            label->setFont(font1);
            label->setCursor(Qt::PointingHandCursor);
            label->setText(name);

            addToUserLabels(label);

        }
    }
    // ve slozce neni slozka s metadata.txt
    if (!isExistName) {
        QLabel *label = new QLabel();
        label->setObjectName(QStringLiteral("label_2"));
        label->setGeometry(QRect(20, 20, 461, 13));
        label->setText("V této složce nemá žádný uživatel data");
        listOfLabels.append(label);
        widgetLayout->addWidget(label);
    }

    int i = 0;
    foreach (UserLabel *label, listOfUserLabels) {
       if (i == 3) break;
        listOfLabels.append(label);
       widgetLayout->addWidget(label);
       // propojeni udalosti na kliknuti s setUser
       connect(label, SIGNAL(clicked(QString)), this, SLOT(setUser(QString)));
       i++;
    }
}

/**
 * Vytvori list pro zobrazeni uzivatelu abecedne
 * @brief InitialWindow::createListOfNames2
 */
void InitialWindow::createListOfNames2() {
    listWidget = new QListWidget();
    listWidget->setCursor(Qt::PointingHandCursor);

    listsOfNamesAlphabetically();

    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSetUser(QListWidgetItem *)));
    listWidget->setSortingEnabled(true);
    listWidget->sortItems();

    verticalLayout->addWidget(listWidget/*, 1, Qt::AlignTop*/);
}

/**
 * Vypise jmena vsech ulozenych uzivatelu
 * @brief InitialWindow::listsOfNames
 */
void InitialWindow::listsOfNamesAlphabetically() {
    QString name;
    // indikuje, zda je ve slozce nejaka slozka s metadata.txt
    bool isExistName = false;
    // ziska list uzivatelskych jmen v datove slozce
    QStringList list = dataManager->listOfFolders();
    QFont font1;
    font1.setUnderline(true);

    foreach (QString s, list) {
        name = dataManager->getNameFromMetadata(s);
        if (!name.isNull()) {
            isExistName = true;

            UserItem *item = new UserItem(s);
            item->setText(name);
            listWidget->addItem(item);
        }
    }
    // ve slozce neni slozka s metadata.txt
    if (!isExistName) {
        listWidget->setEnabled(false);
    }
    else {
        listWidget->setEnabled(true);
    }
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
 * Otevre okno pro vyber slozky a prepise jmena ulozenych uzivatelu
 * @brief InitialWindow::changeWorkspace
 */
void InitialWindow::changeWorkspace() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Otevřít workspace"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    dataManager->FOLDER_NAME = dir;
    workspacePathE->setText(dir);

    // odebrani starych labelu
    deleteLabels();
    listsOfNames();
    listsOfNamesAlphabetically();
}

/**
 * Odebrani starych labelu
 * @brief InitialWindow::deleteLabels
 */
void InitialWindow::deleteLabels() {
    foreach (QWidget *l, listOfLabels) {
        widgetLayout->removeWidget((QWidget *) l);
        listOfLabels.removeOne(l);
        delete l;
    }
    listOfUserLabels.clear();
    listWidget->clear();
}

/**
 * Aktualizace jmen po zobrazeni okna
 * @brief InitialWindow::showEvent
 */
void InitialWindow::showEvent(QShowEvent *) {
    // odebrani starych labelu
    deleteLabels();
    listsOfNames();
    listsOfNamesAlphabetically();
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
 * Prida uzivatelsky label do listu, udrzuje pocet 3 nejnovejsich, radi dle nejnovejsiho
 * @brief InitialWindow::addToUserLabels
 * @param label
 */
void InitialWindow::addToUserLabels(UserLabel *label) {
    int i = 0;
    bool isInserted = false;
    // kdyz neni seznam labelu prazdny, prochazime ho a hledame spravne misto
    if (!listOfUserLabels.isEmpty()) {
        foreach (UserLabel *l, listOfUserLabels) {
            if (l->getDateTime() < label->getDateTime()) {
               listOfUserLabels.insert(i, label);
               isInserted = true;
               break;
            }
            i++;
        }
    }
    // kdyz neni zadny prvek v teto metode vlozen, vlozime na konec
    if (!isInserted) {
        listOfUserLabels.append(label);
    }
}

/**
 * Reakce na zavreni okna krizkem
 * @brief InitialWindow::closeEvent
 */
void InitialWindow::closeEvent(QCloseEvent *) {
    if (!dataManager->isSetMetadata) {
        closeWithoutLogin();
    }
}

/**
 * Zavola setUser() po stisknuti polozky listu
 * @brief InitialWindow::itemClickedSetUser
 */
void InitialWindow::itemClickedSetUser(QListWidgetItem *item) {
    setUser(((UserItem *)item)->username);
}

InitialWindow::~InitialWindow() {

}
/**
 * Vytvori uzivatelsky label
 * @brief UserLabel::UserLabel
 * @param parent
 */
UserLabel::UserLabel(QString username, QDateTime time, QWidget *parent) : QLabel(parent), username(username), dateTime(time) {}

/**
 * Reakce na stisk labelu vola signal clicked
 * @brief UserLabel::mousePressEvent
 * @param event
 */
void UserLabel::mousePressEvent(QMouseEvent *) {
    emit clicked(username);
}

/**
 * Vraci ulozeny datum a cas posledni navstevy
 * @brief UserLabel::getDateTime
 */
QDateTime UserLabel::getDateTime() {
    return dateTime;
}

UserLabel::~UserLabel() {}

/**
 * Vytvori uzivatelskou polozku listu
 * @brief UserItem::UserItem
 * @param parent
 */
UserItem::UserItem(QString username, QListWidget *parent) : QListWidgetItem(parent), username(username) {}

UserItem::~UserItem() {}
