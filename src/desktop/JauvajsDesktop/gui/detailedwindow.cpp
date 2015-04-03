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
    graphicsView->setBackgroundBrush(QBrush(QColor(1, 51, 50), Qt::SolidPattern));
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
        scene->removeItem(textMinX);
        scene->removeItem(horizontalLine);
    }

    horizontalLine = scene->addLine(0, graphicsView->viewport()->height() - BOTTOM_OFFSET, graphicsView->viewport()->width(), graphicsView->viewport()->height() - BOTTOM_OFFSET, QPen(Qt::white));
    verticalLine = scene->addLine(LEFT_OFFSET, 0, LEFT_OFFSET, graphicsView->viewport()->height(), QPen(Qt::white));

    QFont font = QFont("Arial", 6);
    // popis nejvyssi hodnoty Y
    textMaxY = scene->addText(QString::number(sensor->maxY), font);
    textMaxY->setPos(0,0);
    textMaxY->setDefaultTextColor(Qt::white);

    // popis nejmensi hodnoty Y
    textMinY = scene->addText(QString::number(sensor->minY), font);
    textMinY->setPos(0, graphicsView->viewport()->height() - textMinY->boundingRect().height() - BOTTOM_OFFSET);
    textMinY->setDefaultTextColor(Qt::white);

    // popis nejvyssi hodnoty X
    textMaxX = scene->addText(QString::number(graphicsView->viewport()->width() - LEFT_OFFSET) + " [time]", font);
    textMaxX->setPos(graphicsView->viewport()->width() - textMaxX->boundingRect().width(), graphicsView->height() - textMaxX->boundingRect().height());
    textMaxX->setDefaultTextColor(Qt::white);

    // popis nejmensi hodnoty X
    textMinX = scene->addText(QString::number(sensor->minX), font);
    textMinX->setPos(LEFT_OFFSET, graphicsView->viewport()->height() - textMinY->boundingRect().height());
    textMinX->setDefaultTextColor(Qt::white);

    itemsExist = true;
}

/**
 * Vykresli vertikalni cary pro lepsi orientaci v grafu
 * @brief SensorWidget::drawVerticalLines
 */
void DetailedWindow::drawVerticalLines() {
    int interval = 10; // interval car
    int boldInterval = 50; // interval tucnych car
    int width = 1500;
    for (int i = 0; i < width; i += interval) {
        if (i != 0)
        if (i % boldInterval == 0) {
            QPen pen;
            pen.setWidth(2);
            pen.setBrush(QColor(0, 102, 96));
            scene->addLine(LEFT_OFFSET + i, 0, LEFT_OFFSET + i, graphicsView->viewport()->height(), pen);
        }
        else {
            scene->addLine(LEFT_OFFSET + i, 0, LEFT_OFFSET + i, graphicsView->viewport()->height(), QPen(QColor(0, 102, 96)));
        }
    }
}

/**
 * Vykresli horizontalni cary pro lepsi orientaci v grafu
 * @brief SensorWidget::drawVerticalLines
 */
void DetailedWindow::drawHorizontalLines() {
    int numberOfLines; // pocet car
    double interval; // interval car
    int boldInterval = 4; // interval tucnych car
    int width = 1500;
    int height = sensor->maxY - sensor->minY; // skutecna vyska
    numberOfLines = height;
    while (numberOfLines < 10) {
        numberOfLines *= 2;
    }

    interval = (graphicsView->viewport()->height() - BOTTOM_OFFSET) / (double) numberOfLines;
    for (int i = 1; i < numberOfLines; i++) {
        if (i % boldInterval == 0) {
            QPen pen;
            pen.setWidth(2);
            pen.setBrush(QColor(0, 102, 96));
            scene->addLine(0,(int) i * interval, width, (int) i * interval, pen);
        }
        else {
            scene->addLine(0,(int) i * interval, width, (int) i * interval, QPen(QColor(0, 102, 96)));
        }
    }
}

DetailedWindow::~DetailedWindow() {

}


