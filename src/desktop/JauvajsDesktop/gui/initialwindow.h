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

private:
    /** spravce dat */
    DataManager *dataManager;
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;
};

#endif // INITIALWINDOW_H
