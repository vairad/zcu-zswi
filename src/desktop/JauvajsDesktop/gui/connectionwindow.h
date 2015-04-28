#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>

class ConnectionWindow  : public QDialog {
public:
    ConnectionWindow();
    ~ConnectionWindow();
    void createTextEdit();
    void createButtons();

private:
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;
};

#endif // CONNECTIONWINDOW_H
