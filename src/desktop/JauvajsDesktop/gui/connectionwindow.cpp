#include <QTextEdit>
#include <QPushButton>

#include "connectionwindow.h"

ConnectionWindow::ConnectionWindow() {
    this->resize(501, 313);

    setWindowTitle("Okno");

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(20, 20, 20, 20);
    verticalLayout->setAlignment(Qt::AlignTop);

    createTextEdit();
    createButtons();

    this->show();
}

void ConnectionWindow::createTextEdit() {
    QTextEdit *textEdit = new QTextEdit;
    verticalLayout->addWidget(textEdit);
}

/**
 * Vytvori tlacitka
 * @brief InitialWindow::createButtons
 */
void ConnectionWindow::createButtons() {
    QWidget *widgetBT = new QWidget();
    QHBoxLayout *group = new QHBoxLayout(widgetBT);

    // tlacitko vytvorit noveho uzivatele
    QPushButton *bt1 = new QPushButton();
    bt1->setObjectName(QStringLiteral("button"));
    bt1->setText("Button 1");
    group->addWidget(bt1);

    // tlacitko pokracovat bez prihlaseni
    QPushButton *bt2 = new QPushButton();
    bt2->setObjectName(QStringLiteral("button_2"));
    bt2->setText("button 2");
    group->addWidget(bt2);

    verticalLayout->addWidget(widgetBT, 0, Qt::AlignBottom);
}

ConnectionWindow::~ConnectionWindow() {

}

