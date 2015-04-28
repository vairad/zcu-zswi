#include <QLabel>

#include "analysiswindow.h"

/**
 * Vytvori okno pro zobrazeni vysledku analyzy
 * @brief AnalysisWindow::AnalysisWindow
 * @param parent
 */
AnalysisWindow::AnalysisWindow(QWidget *parent) : QDialog(parent) {
    this->resize(501, 313);

    setWindowTitle("Analýza");

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(20, 20, 20, 20);
    verticalLayout->setAlignment(Qt::AlignTop);

    createLabels();

    this->show();
}

/**
 * Vytvori labely
 * @brief InitialWindow::createTitle
 */
void AnalysisWindow::createLabels() {
    // label - pocet namerenych cyklu
    QLabel *label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setMaximumSize(QSize(16777215, 20));
    label->setText("Počet celých naměřených cyklů: xx");
    verticalLayout->addWidget(label);

    // label - prumerna delka cyklu
    QLabel *label2 = new QLabel(this);
    label2->setObjectName(QStringLiteral("label"));
    label2->setMaximumSize(QSize(16777215, 20));
    label2->setText("Průměrná délka cyklů: xx");
    verticalLayout->addWidget(label2);

    // label - anomalie EKG
    QLabel *label3 = new QLabel(this);
    label3->setObjectName(QStringLiteral("label"));
    label3->setMaximumSize(QSize(16777215, 20));
    label3->setText("Vaše EKG je z xx % normální");
    verticalLayout->addWidget(label3);
}

AnalysisWindow::~AnalysisWindow() {

}
