/********************************************************************************
** Form generated from reading UI file 'hlavni.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HLAVNI_H
#define UI_HLAVNI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HlavniClass
{
public:
    QWidget *centralWidget;
    QPushButton *karel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HlavniClass)
    {
        if (HlavniClass->objectName().isEmpty())
            HlavniClass->setObjectName(QStringLiteral("HlavniClass"));
        HlavniClass->resize(600, 400);
        centralWidget = new QWidget(HlavniClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        karel = new QPushButton(centralWidget);
        karel->setObjectName(QStringLiteral("karel"));
        karel->setGeometry(QRect(230, 120, 151, 81));
        HlavniClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HlavniClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        HlavniClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HlavniClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HlavniClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HlavniClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HlavniClass->setStatusBar(statusBar);

        retranslateUi(HlavniClass);

        QMetaObject::connectSlotsByName(HlavniClass);
    } // setupUi

    void retranslateUi(QMainWindow *HlavniClass)
    {
        HlavniClass->setWindowTitle(QApplication::translate("HlavniClass", "Hlavni", 0));
#ifndef QT_NO_WHATSTHIS
        karel->setWhatsThis(QApplication::translate("HlavniClass", "<html><head/><body><p>fghgjnhngf</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        karel->setText(QApplication::translate("HlavniClass", "Klikni na m\304\233!", 0));
    } // retranslateUi

};

namespace Ui {
    class HlavniClass: public Ui_HlavniClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HLAVNI_H
