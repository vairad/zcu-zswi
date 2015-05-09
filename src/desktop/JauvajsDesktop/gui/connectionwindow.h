#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include "core/arduinominer.h"

class ConnectionWindow : public QDialog {
   Q_OBJECT
public:
    explicit ConnectionWindow(ArduinoMiner *arduinoMiner, QWidget *parent = 0);
    ~ConnectionWindow();
    void createTextEdit();
    void createButtons();
    QTextEdit *textEdit;

public slots:
    void disconnectArduino();
    void serialReceived(QString);

private:
    /** vertikalni layout */
    QVBoxLayout *verticalLayout;
    ArduinoMiner *arduinoMiner;
};
#endif // CONNECTIONWINDOW_H
