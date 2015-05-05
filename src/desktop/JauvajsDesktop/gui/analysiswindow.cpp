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

    layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignTop);

    createTitle();
    createLabelsForDescriptionOfResults();
    createLabelsForResults();

    this->show();
}

/**
 * Vytvori uvodni nadpis
 * @brief AnalysisWindow::createTitle
 */
void AnalysisWindow::createTitle() {
    // pismo pro nadpis
    QFont font;
    font.setFamily(QStringLiteral("Calibri"));
    font.setPointSize(16);
    font.setBold(true);
    font.setWeight(75);

    // uvodni label (nadpis)
    QLabel *titleL = new QLabel(this);
    titleL->setText("Výsledek analýzy EKG");
    titleL->setFont(font);
    layout->addWidget(titleL, 0, 0, 1, 2);

    // cara pod nadpisem
    QFrame* lineF = new QFrame();
    lineF->setFrameShape(QFrame::HLine);
    layout->addWidget(lineF, 1, 0, 1, 2);
}

/**
 * Vytvori popisy vysledku analyzy do leveho sloupce
 * @brief AnalysisWindow::createLabelsForResults
 */
void AnalysisWindow::createLabelsForDescriptionOfResults() {
    // label - pocet namerenych cyklu
    QLabel *label = new QLabel(this);
    label->setText("Počet celých naměřených cyklů:");
    layout->addWidget(label, 2, 0);

    // label - prumerna delka cyklu
    QLabel *label2 = new QLabel(this);
    label2->setText("Průměrná délka cyklu:");
    layout->addWidget(label2, 3, 0);

    // label - procento normalnich srdecnich cyklu
    QLabel *label3 = new QLabel(this);
    label3->setText("Z naměřených srdečních cyklů je v normě:");
    layout->addWidget(label3, 4, 0);

    // label - procento pravidelnych srdecnich cyklu
    QLabel *label4 = new QLabel(this);
    label4->setText("Z naměřených srdečních cyklů je pravidelných:");
    layout->addWidget(label4, 5, 0);
}

/**
 * Vypise vysledky analyzy do praveho sloupce
 * @brief InitialWindow::createTitle
 */
void AnalysisWindow::createLabelsForResults() {
    // Ziskani vysledku analyzy
    AnalyserEKG *analyser = new AnalyserEKG(values.toVector().toStdVector());
    analyser->analyse();

    int numberOfCycles = analyser->getNumberOfCycles();
    float averageCycleDuratio = analyser->getAverageCycleDuration();
    float normalityPercentage = analyser->getNormalityPercentage();
    float regularityPercentage = analyser->getRegularityPercentage();

    // Pismo pro hodnoty vysledku analyzy
    QFont fontForValues;
    fontForValues.setBold(true);

    // Pocet namerenych cyklu
    QLabel *numberOfCyclesL = new QLabel(this);
    numberOfCyclesL->setText(QString::number(numberOfCycles));
    numberOfCyclesL->setFont(fontForValues);
    layout->addWidget(numberOfCyclesL, 2, 1, Qt::AlignRight);

    // Prumerna delka cyklu
    QLabel *averageCycleDurationL = new QLabel(this);
    averageCycleDurationL->setText(QString::number(averageCycleDuratio) + " s");
    averageCycleDurationL->setFont(fontForValues);
    layout->addWidget(averageCycleDurationL, 3, 1, Qt::AlignRight);

    // Procento normalnich srdecnich cyklu
    QLabel *normalityPercentageL = new QLabel(this);
    normalityPercentageL->setText(QString::number(normalityPercentage) + " %");
    normalityPercentageL->setFont(fontForValues);
    layout->addWidget(normalityPercentageL, 4, 1, Qt::AlignRight);

    // Procento pravidelnych srdecnich cyklu
    QLabel *regularityPercentageL = new QLabel(this);
    regularityPercentageL->setText(QString::number(regularityPercentage) + " %");
    regularityPercentageL->setFont(fontForValues);
    layout->addWidget(regularityPercentageL, 5, 1, Qt::AlignRight);
}

AnalysisWindow::~AnalysisWindow() {

}

