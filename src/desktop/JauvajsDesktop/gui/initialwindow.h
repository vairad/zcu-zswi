#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QListWidget>
#include "core/datamanager.h"

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
    void createButtons();

public slots:
    void setUser(QString username);

private:
    /** spravce dat */
    DataManager *dataManager;
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;
    /** hlavni okno aplikace */
    QWidget *mainWindow;
};

/**
 * Reprezentace labelu, ktery narozdil od QLabel umoznuje signal clicked
 * @brief The UserLabel class
 */
class UserLabel : public QLabel {
    Q_OBJECT
public:
    UserLabel(QString username, QWidget *parent = 0);
    ~UserLabel();

signals:
    void clicked(QString username);

protected:
    void mousePressEvent(QMouseEvent *);

private:
    /** uzivatelske jmeno prislusici labelu */
    QString username;
};

#endif // INITIALWINDOW_H
