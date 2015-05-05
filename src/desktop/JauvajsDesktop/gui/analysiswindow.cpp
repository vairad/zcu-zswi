#include <QLabel>
#include <QVector>

#include <QDebug>

#include "analysiswindow.h"
#include "analysis/analyserekg.h"

/**
 * Vytvori okno pro zobrazeni vysledku analyzy
 * @brief AnalysisWindow::AnalysisWindow
 * @param parent
 */
AnalysisWindow::AnalysisWindow(QList<float> values, QWidget *parent) : QDialog(parent), values(values) {
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
    QLabel *label1 = new QLabel(this);
    label1->setObjectName(QStringLiteral("label"));
    label1->setMaximumSize(QSize(16777215, 20));
    QFont font;
    font.setFamily(QStringLiteral("Calibri"));
    font.setPointSize(16);
    font.setBold(true);
    font.setWeight(75);
    label1->setFont(font);
    label1->setText("Výsledek analýzy EKG");

    verticalLayout->addWidget(label1);

    AnalyserEKG *analyser = new AnalyserEKG(values.toVector().toStdVector());

   // qDebug() << "Analyzator vytvořen";

    analyser->analyse();

    int numberOfCycles = analyser->getNumberOfCycles();
    float averageCycleDuratio = analyser->getAverageCycleDuration();
    float normalityPercentage = analyser->getNormalityPercentage();

    // label - pocet namerenych cyklu
    QLabel *label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setMaximumSize(QSize(16777215, 20));
    label->setText("Počet celých naměřených cyklů: " + QString::number(numberOfCycles));
    verticalLayout->addWidget(label);

    // label - prumerna delka cyklu
    QLabel *label2 = new QLabel(this);
    label2->setObjectName(QStringLiteral("label"));
    label2->setMaximumSize(QSize(16777215, 20));
    label2->setText("Průměrná délka cyklu: " + QString::number(averageCycleDuratio) + " s");
    verticalLayout->addWidget(label2);

    // label - anomalie EKG
    QLabel *label3 = new QLabel(this);
    label3->setObjectName(QStringLiteral("label"));
    label3->setMaximumSize(QSize(16777215, 20));
    label3->setText("Z naměřených srdečních cyklů je " + QString::number(normalityPercentage) + "% v normě.");
    verticalLayout->addWidget(label3);
}

AnalysisWindow::~AnalysisWindow() {

}

