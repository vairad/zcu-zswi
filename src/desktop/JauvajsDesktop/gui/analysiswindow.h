#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QList>

/**
 * Okno pro zobrazeni vysledku analyzy
 * @brief The AnalysisWindow class
 */
class AnalysisWindow : public QDialog {
public:
    AnalysisWindow(QList<float> values, QWidget *parent);
    ~AnalysisWindow();
    void createLabels();

private:
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;

    QList<float> values;
};

#endif // ANALYSISWINDOW_H
