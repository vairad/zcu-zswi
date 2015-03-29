#ifndef HLAVNI_H
#define HLAVNI_H

#include <QMainWindow>

namespace Ui {
class Hlavni;
}

class Hlavni : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hlavni(QWidget *parent = 0);
    ~Hlavni();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Hlavni *ui;
};

#endif // HLAVNI_H
