#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>

#include "core/datamanager.h"

/**
 * Reprezentace labelu, ktery narozdil od QLabel umoznuje signal clicked
 * @brief The UserLabel class
 */
class UserLabel : public QLabel {
    Q_OBJECT
public:
    UserLabel(QString username, QDateTime time, QWidget *parent = 0);
    ~UserLabel();
    QDateTime getDateTime();

signals:
    void clicked(QString username);

protected:
    void mousePressEvent(QMouseEvent *);

/*private:*/
public:
    /** uzivatelske jmeno prislusici labelu */
    QString username;
    /** datum a cas posledni navstevy */
    QDateTime dateTime;
};

/**
 * Reprezentace polozky listu
 * @brief The UserLabel class
 */
class UserItem : public QListWidgetItem {
    //Q_OBJECT
public:
    UserItem(QString username, QListWidget *parent = 0);
    ~UserItem();
    /** uzivatelske jmeno prislusici polozce */
    QString username;
};

/**
 * Uvodni okno pro vyber jiz ulozenych uzivatelu,
 * vytvoreni noveho nebo pokracovani do promotion
 * @brief The InitialWindow class
 */
class InitialWindow : public QDialog {
    Q_OBJECT
public:
    explicit InitialWindow(DataManager *dataManager, QWidget *parent = 0);
    ~InitialWindow();
    void createTitle();
    void createListOfNames();
    void createListOfNames2();
    void listsOfNames();
    void listsOfNamesAlphabetically();
    void createButtons();
    void deleteLabels();
    //bool compareUserLabels(QWidget *left, QWidget *right);
    void addToUserLabels(UserLabel *label);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

public slots:
    void changeWorkspace();
    void setUser(QString username);
    void closeWithoutLogin();
    void createNewUser();
    void itemClickedSetUser(QListWidgetItem *item);

private:
    /** spravce dat */
    DataManager *dataManager;
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;
    /** hlavni okno aplikace */
    QWidget *mainWindow;
    /** list vytvorenych labelu jmen uzivatelu */
    QList<QWidget *> listOfLabels;
    /** list 3 uzivatelu, kteri pouzivali aplikaci naposledy */
    QList<UserLabel *> listOfUserLabels;
    /** layout pro widget na zobrazeni jmen uzivatelu */
    QVBoxLayout *widgetLayout;
    /** label pro cestu k workspace */
    QLineEdit *workspacePathE;
    /** list pro zobrazeni uzivatelu abecedne */
    QListWidget *listWidget;
};

#endif // INITIALWINDOW_H
