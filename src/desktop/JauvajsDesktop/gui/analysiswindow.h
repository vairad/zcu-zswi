#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include <QDialog>
#include <QVBoxLayout>

/**
 * Okno pro zobrazeni vysledku analyzy
 * @brief The AnalysisWindow class
 */
class AnalysisWindow : public QDialog {
public:
    AnalysisWindow(QWidget *parent);
    ~AnalysisWindow();
    void createLabels();

private:
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;
};

#endif // ANALYSISWINDOW_H
