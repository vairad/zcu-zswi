#include "detailedwindow.h"
#include <QHBoxLayout>
#include <QGraphicsView>

/**
 * Vytvori detailni okno senzoru
 * @brief DetailedWindow::DetailedWindow
 * @param sensor senzor pro detalni zobrazeni
 * @param parent
 */
DetailedWindow::DetailedWindow(IDisplayable *sensor, QWidget *parent) : QDialog(parent), sensor(sensor) {
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
    graphicsView->setBackgroundBrush(QBrush(QColor(48, 128, 20), Qt::SolidPattern));
    graphicsView->setFrameStyle(0);

    layout->addWidget(graphicsView);
    itemsExist = false;
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v detailnim okne v danem case
 * @brief SensorWidget::update
 * @param value hodnota
 */
void DetailedWindow::update(double value) {
    int y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * graphicsView->viewport()->height());
    int lastY = graphicsView->viewport()->height() - ((sensor->lastValue - sensor->minY) / (sensor->maxY - sensor->minY) * graphicsView->viewport()->height());

    if (sensor->lastValue != -1) {
        scene->addLine(sensor->time, lastY, sensor->time+1, y, QPen(Qt::white));
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
}

/**
 * Vykresli popisy grafu
 * BUDE UPRAVENO NA PODROBNEJSI POPISY, ZATIM STEJNE JAKO V SENSORWIDGET
 * @brief SensorWidget::drawNumbers
 */
void DetailedWindow::drawNumbers() {
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

DetailedWindow::~DetailedWindow() {

}


