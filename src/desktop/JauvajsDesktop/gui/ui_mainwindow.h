/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionO_aplikaci;
    QAction *actionZav_t;
    QAction *actionU_ivatelsk_nastaven;
    QAction *actionZm_na_u_ivatele;
    QAction *actionVy_istit_v_e;
    QAction *actionOtev_t;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QMenuBar *menuBar;
    QMenu *menuSoubor;
    QMenu *menuN_pov_da;
    QMenu *menuZobrazit;
    QMenu *menuNastaven;
    QMenu *menu_pravy;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(756, 408);
        actionO_aplikaci = new QAction(MainWindow);
        actionO_aplikaci->setObjectName(QStringLiteral("actionO_aplikaci"));
        actionZav_t = new QAction(MainWindow);
        actionZav_t->setObjectName(QStringLiteral("actionZav_t"));
        actionZav_t->setEnabled(true);
        actionU_ivatelsk_nastaven = new QAction(MainWindow);
        actionU_ivatelsk_nastaven->setObjectName(QStringLiteral("actionU_ivatelsk_nastaven"));
        actionZm_na_u_ivatele = new QAction(MainWindow);
        actionZm_na_u_ivatele->setObjectName(QStringLiteral("actionZm_na_u_ivatele"));
        actionVy_istit_v_e = new QAction(MainWindow);
        actionVy_istit_v_e->setObjectName(QStringLiteral("actionVy_istit_v_e"));
        actionOtev_t = new QAction(MainWindow);
        actionOtev_t->setObjectName(QStringLiteral("actionOtev_t"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setLineWidth(1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setEnabled(true);
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 738, 349));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents_2->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_2->setSizePolicy(sizePolicy1);
        scrollAreaWidgetContents_2->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 756, 21));
        menuSoubor = new QMenu(menuBar);
        menuSoubor->setObjectName(QStringLiteral("menuSoubor"));
        menuN_pov_da = new QMenu(menuBar);
        menuN_pov_da->setObjectName(QStringLiteral("menuN_pov_da"));
        menuZobrazit = new QMenu(menuBar);
        menuZobrazit->setObjectName(QStringLiteral("menuZobrazit"));
        menuNastaven = new QMenu(menuBar);
        menuNastaven->setObjectName(QStringLiteral("menuNastaven"));
        menu_pravy = new QMenu(menuBar);
        menu_pravy->setObjectName(QStringLiteral("menu_pravy"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSoubor->menuAction());
        menuBar->addAction(menu_pravy->menuAction());
        menuBar->addAction(menuZobrazit->menuAction());
        menuBar->addAction(menuNastaven->menuAction());
        menuBar->addAction(menuN_pov_da->menuAction());
        menuSoubor->addAction(actionOtev_t);
        menuSoubor->addAction(actionZav_t);
        menuN_pov_da->addAction(actionO_aplikaci);
        menuNastaven->addAction(actionU_ivatelsk_nastaven);
        menuNastaven->addAction(actionZm_na_u_ivatele);
        menu_pravy->addAction(actionVy_istit_v_e);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "E-health", 0));
        actionO_aplikaci->setText(QApplication::translate("MainWindow", "O aplikaci", 0));
        actionZav_t->setText(QApplication::translate("MainWindow", "Zav\305\231\303\255t", 0));
        actionU_ivatelsk_nastaven->setText(QApplication::translate("MainWindow", "U\305\276ivatelsk\303\251 nastaven\303\255", 0));
        actionZm_na_u_ivatele->setText(QApplication::translate("MainWindow", "Zm\304\233na u\305\276ivatele", 0));
        actionVy_istit_v_e->setText(QApplication::translate("MainWindow", "Vy\304\215istit v\305\241e", 0));
        actionOtev_t->setText(QApplication::translate("MainWindow", "Otev\305\231\303\255t", 0));
        menuSoubor->setTitle(QApplication::translate("MainWindow", "Soubor", 0));
        menuN_pov_da->setTitle(QApplication::translate("MainWindow", "N\303\241pov\304\233da", 0));
        menuZobrazit->setTitle(QApplication::translate("MainWindow", "Zobrazit", 0));
        menuNastaven->setTitle(QApplication::translate("MainWindow", "Nastaven\303\255", 0));
        menu_pravy->setTitle(QApplication::translate("MainWindow", "\303\232pravy", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
