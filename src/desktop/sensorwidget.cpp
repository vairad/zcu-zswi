#include "sensorwidget.h"
#include <QApplication>
#include "loadfile.h"
#include "ui_mainwindow.h"
#include <QGraphicsTextItem>

SensorWidget::SensorWidget(QVBoxLayout *vLayout, QMenu *menuZobrazit, IDisplayable *sensor, QWidget *parent) : menuZobrazit(menuZobrazit), sensor(sensor), QWidget(parent) {
    this->setObjectName(QStringLiteral("widget"));
    this->setEnabled(true);
    this->setMinimumSize(QSize(0, 100));
    this->setMaximumSize(QSize(16777215, 100));
    this->setCursor(QCursor(Qt::ArrowCursor));
    this->setAutoFillBackground(false);
    vLayout->addWidget(this, 0, Qt::AlignTop);

    createLayout();
    createLeftBox();
    createGraphicsView();
    createAction();
    itemsExist = false;
}

/**
 * Nastavi widgetu layout
 * @brief SensorWidget::createLayout
 */
void SensorWidget::createLayout() {
    layout = new QHBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);
    layout->setObjectName(QStringLiteral("horizontalLayout"));
    layout->setContentsMargins(0, 0, 0, 0);
}

/**
 * Vykresli levy box s tlacikem a popisem senzoru
 * @brief SensorWidget::createLeftBox
 */
void SensorWidget::createLeftBox() {
    widget = new QWidget(this);
    widget->setObjectName(QStringLiteral("widget"));
    widget->setMinimumSize(QSize(150, 0));
    widget->setMaximumSize(QSize(150, 16777215));

    button = new QPushButton(widget);
    button->setObjectName(QStringLiteral("button"));
    button->setGeometry(QRect(10, 50, 131, 23));
    button->setText(QApplication::translate("MainWindow", "Zah\303\241jit z\303\241znam", 0));

    label = new QLabel(widget);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(50, 20, 47, 13));
    label->setScaledContents(false);
    label->setAlignment(Qt::AlignCenter);
    label->setText(QApplication::translate("MainWindow", sensor->getName().toStdString().c_str(), 0));

    layout->addWidget(widget);
}

/**
 * Vykresli graficke okno
 * @brief SensorWidget::createGraphicsView
 */
void SensorWidget::createGraphicsView() {
    graphicsView = new QGraphicsView(this);
    graphicsView->setObjectName(QStringLiteral("graphicsView"));
    graphicsView->setEnabled(true);
    graphicsView->setMinimumSize(QSize(0, 100));
    graphicsView->setMaximumSize(QSize(16777215, 100));
    graphicsView->setDragMode(QGraphicsView::NoDrag);
    graphicsView->setCacheMode(QGraphicsView::CacheNone);
    graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    graphicsView->setRubberBandSelectionMode(Qt::ContainsItemShape);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF(this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height())));

    graphicsView->setScene(scene);
    graphicsView->setBackgroundBrush(QBrush(QColor(48, 128, 20), Qt::SolidPattern));
    graphicsView->setFrameStyle(0);

    layout->addWidget(graphicsView);
}

/**
 * Vytvori akci pro Menu -> Zobrazit
 * @brief SensorWidget::createAction
 */
void SensorWidget::createAction() {
    action1 = new QAction(this);
    action1->setObjectName(QStringLiteral("action"));
    action1->setCheckable(true);
    action1->setChecked(true);
    action1->setText(QApplication::translate("SensorWidget", sensor->getName().toStdString().c_str(), 0));
    menuZobrazit->addAction(action1);

    QMetaObject::connectSlotsByName(this);
}

void SensorWidget::zobrazit() {

}

/**
 * Zmena velikosti sceny pri zmene velikosti okna
 * @brief SensorWidget::resizeEvent
 * @param e
 */
void SensorWidget::resizeEvent(QResizeEvent *e) {
    graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QPointF(graphicsView->viewport()->width(), graphicsView->viewport()->height())));
    drawNumbers();
}

/**
 * Pocatecni nastaveni velikosti sceny
 * @brief SensorWidget::setUp
 */
void SensorWidget::setUp() {
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF(this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height())));
    drawNumbers();
}

/**
 * Zobrazeni nebo skryti grafu pro senzor
 * @brief MainWindow::on_actionEKG_toggled
 * @param arg1
 */
void SensorWidget::on_action_toggled(bool arg1) {
    if (arg1) {
       this->show();
    }
    else {
       this->hide();
    }
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v danem case
 * @brief SensorWidget::update
 * @param value
 */
void SensorWidget::update(double value) {
    int y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * graphicsView->viewport()->height());
    if (sensor->lastY != -1) {
        scene->addLine(sensor->time, sensor->lastY, sensor->time+1, y, QPen(Qt::white));
        graphicsView->viewport()->repaint();
    }

    sensor->lastY = y;
    sensor->time++;
}

/**
 * Udalost na stisk Zahajit zaznam
 * @brief SensorWidget::on_button_clicked
 */
void SensorWidget::on_button_clicked() {
    new LoadFile(this);
}

/**
 * @brief SensorWidget::drawNumbers
 */
void SensorWidget::drawNumbers() {
    if (itemsExist) {
        // odebrani starych hodnot
        scene->removeItem(textMaxY);
        scene->removeItem(textMinY);
        scene->removeItem(textMaxX);
    }

    QFont font = QFont("Arial", 6);
    // popis nejvyssi hodnoty Y
    textMaxY = scene->addText(QString::number(sensor->maxY), font);
    textMaxY->setPos(0,0);
    textMaxY->setDefaultTextColor(Qt::white);

    // popis nejmensi hodnoty Y
    textMinY = scene->addText(QString::number(sensor->minY), font);
    QFontMetrics *fm = new QFontMetrics(font);
    textMinY->setPos(0, graphicsView->viewport()->height() - fm->height()*2);
    textMinY->setDefaultTextColor(Qt::white);

    // popis nejvyssi hodnoty X
    textMaxX = scene->addText(QString::number(graphicsView->viewport()->width()), font);
    textMaxX->setPos(graphicsView->viewport()->width() - fm->width(QString::number(graphicsView->viewport()->width()))*2, graphicsView->viewport()->height() - fm->height()*2);
    textMaxX->setDefaultTextColor(Qt::white);
    itemsExist = true;
}

SensorWidget::~SensorWidget() {

}

