#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

class HelpWindow : public QDialog {
    Q_OBJECT
public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();
    void createTextEdit();
    void createButton();
    /** pole pro zobrazeni napovedy */
    QTextEdit *textEdit;
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;
};

#endif // HELPWINDOW_H
