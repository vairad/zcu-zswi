#include "gui/sensorwidget.h"
#include <QApplication>
#include "loadfile.h"
#include <QGraphicsTextItem>

SensorWidget::SensorWidget(QVBoxLayout *vLayout, QMenu *menuZobrazit, IDisplayable *sensor, QWidget *parent) : menuZobrazit(menuZobrazit), QWidget(parent) {
    this->sensor = sensor;

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

    verticalLinesInterval = 1;
    verticalLinesBoldInterval = 5;
    minNumberOfHorizontalLines = 6;

    detailedWindow = new DetailedWindow(sensor);
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
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF(this->graphicsView->width(), this->graphicsView->height())));

    graphicsView->setScene(scene);
    graphicsView->setBackgroundBrush(QBrush(QColor(1, 51, 50), Qt::SolidPattern));
    graphicsView->setFrameStyle(0);
    graphicsView->setCursor(Qt::PointingHandCursor);

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
    drawVerticalLines();
    drawNumbers();
}

/**
 * @brief mousePressEvent
 * @param event
 */
void SensorWidget::mousePressEvent(QMouseEvent *event) {
    detailedWindow->showNormal();
}

/**
 * Pocatecni nastaveni velikosti sceny
 * @brief SensorWidget::setUp
 */
void SensorWidget::setUp() {
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF(this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height())));
    drawNumbers();
    drawVerticalLines();
    drawHorizontalLines();
    detailedWindow->showMinimized();
    detailedWindow->hide();
    detailedWindow->setUp();
}

/**
 * Zobrazeni nebo skryti grafu pro senzor
 * @brief MainWindow::on_actionEKG_toggled
 * @param arg1
 */
void SensorWidget::on_action_toggled(bool arg1) {
    if (arg1) {
        this->show();
        action1->setChecked(true);
        visible(true);
    }
    else {
        this->hide();
        action1->setChecked(false);
        visible(false);
    }
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v danem case
 * @brief SensorWidget::update
 * @param value
 */
void SensorWidget::update(double value) {
    int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;

    int y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);
    int lastY = graphicsView->viewport()->height() - ((sensor->lastValue - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);

    if (sensor->lastValue != -1) {
        scene->addLine(LEFT_OFFSET + sensor->time, lastY, LEFT_OFFSET + sensor->time+1, y, QPen(Qt::white));
        graphicsView->viewport()->repaint();
    }

    detailedWindow->update(value);

    sensor->lastValue = value;
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
 * Vrati IDisplayable senzor
 * @brief SensorWidget::getSensor
 * @return
 */
IDisplayable *SensorWidget::getSensor() {
    return sensor;
}

SensorWidget::~SensorWidget() {

}

