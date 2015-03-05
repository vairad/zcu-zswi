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

class Ui_Hlavni
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Hlavni)
    {
        if (Hlavni->objectName().isEmpty())
            Hlavni->setObjectName(QStringLiteral("Hlavni"));
        Hlavni->resize(400, 300);
        centralWidget = new QWidget(Hlavni);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 110, 111, 31));
        Hlavni->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Hlavni);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        Hlavni->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Hlavni);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Hlavni->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Hlavni);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Hlavni->setStatusBar(statusBar);

        retranslateUi(Hlavni);

        QMetaObject::connectSlotsByName(Hlavni);
    } // setupUi

    void retranslateUi(QMainWindow *Hlavni)
    {
        Hlavni->setWindowTitle(QApplication::translate("Hlavni", "Hlavni", 0));
        pushButton->setText(QApplication::translate("Hlavni", "Klik", 0));
    } // retranslateUi

};

namespace Ui {
    class Hlavni: public Ui_Hlavni {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HLAVNI_H
