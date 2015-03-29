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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_nast;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QMenu *menuSoubor;
    QMenu *menuN_pov_da;
    QMenu *menuZobrazit;
    QMenu *menuNastaven;
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
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 532, 349));
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

        widget_nast = new QWidget(centralWidget);
        widget_nast->setObjectName(QStringLiteral("widget_nast"));
        sizePolicy1.setHeightForWidth(widget_nast->sizePolicy().hasHeightForWidth());
        widget_nast->setSizePolicy(sizePolicy1);
        widget_nast->setMinimumSize(QSize(200, 0));
        widget_nast->setMaximumSize(QSize(200, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_nast);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(widget_nast);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 91, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 50, 91, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 30, 47, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 50, 47, 20));

        verticalLayout_2->addWidget(groupBox);


        horizontalLayout->addWidget(widget_nast);

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
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSoubor->menuAction());
        menuBar->addAction(menuZobrazit->menuAction());
        menuBar->addAction(menuNastaven->menuAction());
        menuBar->addAction(menuN_pov_da->menuAction());
        menuSoubor->addAction(actionZav_t);
        menuN_pov_da->addAction(actionO_aplikaci);
        menuNastaven->addAction(actionU_ivatelsk_nastaven);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "E-health", 0));
        actionO_aplikaci->setText(QApplication::translate("MainWindow", "O aplikaci", 0));
        actionZav_t->setText(QApplication::translate("MainWindow", "Zav\305\231\303\255t", 0));
        actionU_ivatelsk_nastaven->setText(QApplication::translate("MainWindow", "U\305\276ivatelsk\303\251 nastaven\303\255", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Nastaven\303\255", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_3->setText(QApplication::translate("MainWindow", "Jm\303\251no:", 0));
        label_4->setText(QApplication::translate("MainWindow", "P\305\231\303\255jmen\303\255:", 0));
        menuSoubor->setTitle(QApplication::translate("MainWindow", "Soubor", 0));
        menuN_pov_da->setTitle(QApplication::translate("MainWindow", "N\303\241pov\304\233da", 0));
        menuZobrazit->setTitle(QApplication::translate("MainWindow", "Zobrazit", 0));
        menuNastaven->setTitle(QApplication::translate("MainWindow", "Nastaven\303\255", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
