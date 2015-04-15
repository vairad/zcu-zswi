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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QLabel *popisekStav;
    QLabel *label_3;
    QPushButton *tlacitkoPripojit;
    QPushButton *tlacitkoOdpojit;
    QPushButton *tlacitkoHledejZarizeni;
    QLabel *label_2;
    QLineEdit *poleKOdeslani;
    QLabel *label_4;
    QPushButton *tlacitkoOdeslat;
    QLabel *popisekStavSpojeni;
    QLabel *label;
    QTextEdit *poleLog;
    QListView *listView;
    QSpacerItem *horizontalSpacer;
    QTextEdit *polePrijataData;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(749, 481);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        popisekStav = new QLabel(groupBox);
        popisekStav->setObjectName(QStringLiteral("popisekStav"));
        popisekStav->setGeometry(QRect(10, 10, 231, 31));
        QFont font;
        font.setPointSize(12);
        popisekStav->setFont(font);
        popisekStav->raise();

        gridLayout->addWidget(groupBox, 4, 0, 3, 4);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        tlacitkoPripojit = new QPushButton(centralWidget);
        tlacitkoPripojit->setObjectName(QStringLiteral("tlacitkoPripojit"));
        tlacitkoPripojit->setEnabled(false);

        gridLayout->addWidget(tlacitkoPripojit, 3, 0, 1, 3);

        tlacitkoOdpojit = new QPushButton(centralWidget);
        tlacitkoOdpojit->setObjectName(QStringLiteral("tlacitkoOdpojit"));
        tlacitkoOdpojit->setEnabled(true);

        gridLayout->addWidget(tlacitkoOdpojit, 3, 3, 1, 1);

        tlacitkoHledejZarizeni = new QPushButton(centralWidget);
        tlacitkoHledejZarizeni->setObjectName(QStringLiteral("tlacitkoHledejZarizeni"));

        gridLayout->addWidget(tlacitkoHledejZarizeni, 0, 0, 2, 4);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 10, 0, 1, 1);

        poleKOdeslani = new QLineEdit(centralWidget);
        poleKOdeslani->setObjectName(QStringLiteral("poleKOdeslani"));

        gridLayout->addWidget(poleKOdeslani, 6, 4, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 5, 4, 1, 1);

        tlacitkoOdeslat = new QPushButton(centralWidget);
        tlacitkoOdeslat->setObjectName(QStringLiteral("tlacitkoOdeslat"));
        tlacitkoOdeslat->setEnabled(true);

        gridLayout->addWidget(tlacitkoOdeslat, 7, 4, 1, 1);

        popisekStavSpojeni = new QLabel(centralWidget);
        popisekStavSpojeni->setObjectName(QStringLiteral("popisekStavSpojeni"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        popisekStavSpojeni->setFont(font1);

        gridLayout->addWidget(popisekStavSpojeni, 10, 1, 1, 4);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label, 7, 0, 1, 1);

        poleLog = new QTextEdit(centralWidget);
        poleLog->setObjectName(QStringLiteral("poleLog"));
        poleLog->setReadOnly(true);

        gridLayout->addWidget(poleLog, 8, 0, 2, 4);

        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));

        gridLayout->addWidget(listView, 2, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 6, 5, 1, 1);

        polePrijataData = new QTextEdit(centralWidget);
        polePrijataData->setObjectName(QStringLiteral("polePrijataData"));
        polePrijataData->setReadOnly(true);

        gridLayout->addWidget(polePrijataData, 1, 4, 4, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 749, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Stav aplikace", 0));
        popisekStav->setText(QApplication::translate("MainWindow", "Ned\304\233l\303\241m nic", 0));
        label_3->setText(QApplication::translate("MainWindow", "P\305\231ijat\303\241 data:", 0));
        tlacitkoPripojit->setText(QApplication::translate("MainWindow", "P\305\231ipojit", 0));
        tlacitkoOdpojit->setText(QApplication::translate("MainWindow", "Odpojit", 0));
        tlacitkoHledejZarizeni->setText(QApplication::translate("MainWindow", "Hledat za\305\231\303\255zen\303\255", 0));
        label_2->setText(QApplication::translate("MainWindow", "Stav:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Data k odesl\303\241n\303\255:", 0));
        tlacitkoOdeslat->setText(QApplication::translate("MainWindow", "Odeslat", 0));
        popisekStavSpojeni->setText(QApplication::translate("MainWindow", "Nep\305\231ipojeno", 0));
        label->setText(QApplication::translate("MainWindow", "Z\303\241znamy:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
