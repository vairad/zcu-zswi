#include "detailedwindow.h"
#include <QHBoxLayout>
#include <QGraphicsView>

/**
 * Vytvori detailni okno senzoru
 * @brief DetailedWindow::DetailedWindow
 * @param sensor senzor pro detalni zobrazeni
 * @param parent
 */
DetailedWindow::DetailedWindow(IDisplayable *sensor, QWidget *parent) : QDialog(parent) {
    this->sensor = sensor;

    setWindowTitle(sensor->getName().toStdString().c_str() + tr(" - detail senzoru"));
    QHBoxLayout *layout = new QHBoxLayout();
    this->setLayout(layout);
    this->resize(1000, 200);

    graphicsView = new QGraphicsView(this);
    graphicsView->setObjectName(QStringLiteral("graphicsView"));
    graphicsView->setEnabled(true);
    graphicsView->setMinimumSize(QSize(400, 200));
    graphicsView->setMaximumSize(QSize(16777215, 200));
    graphicsView->setDragMode(QGraphicsView::NoDrag);
    graphicsView->setCacheMode(QGraphicsView::CacheNone);
    graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    graphicsView->setRubberBandSelectionMode(Qt::ContainsItemShape);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF(this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height())));

    graphicsView->setScene(scene);
    graphicsView->setBackgroundBrush(QBrush(QColor(1, 51, 50), Qt::SolidPattern));
    graphicsView->setFrameStyle(0);

    layout->addWidget(graphicsView);

    verticalLinesInterval = 10;
    verticalLinesBoldInterval = 50;
    minNumberOfHorizontalLines = 10;
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v detailnim okne v danem case
 * @brief SensorWidget::update
 * @param value hodnota
 */
void DetailedWindow::update(double value) {
    int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;

    int y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);
    int lastY = graphicsView->viewport()->height() - ((sensor->lastValue - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);

    if (sensor->lastValue != -1) {
        scene->addLine(LEFT_OFFSET + sensor->time, lastY, LEFT_OFFSET + sensor->time+1, y, QPen(Qt::white));
        graphicsView->viewport()->repaint();
    }
}

/**
 * Zmena velikosti sceny pri zmene velikosti okna
 * @brief SensorWidget::resizeEvent
 * @param e
 */
void DetailedWindow::resizeEvent(QResizeEvent *e) {
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF(graphicsView->viewport()->width(), graphicsView->viewport()->height())));
    drawNumbers();
}

/**
 * Pocatecni nastaveni velikosti sceny
 * @brief DetailedWindow::setUp
 */
void DetailedWindow::setUp() {
    resizeEvent(NULL);
    drawVerticalLines();
    drawHorizontalLines();
    drawNumbers();
}

DetailedWindow::~DetailedWindow() {

}


