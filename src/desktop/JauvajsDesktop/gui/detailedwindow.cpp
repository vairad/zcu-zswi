#include <QHBoxLayout>
#include <QGraphicsView>

#include "detailedwindow.h"

/**
 * Vytvori detailni okno senzoru
 * @brief DetailedWindow::DetailedWindow
 * @param sensor senzor pro detalni zobrazeni
 * @param parent
 */
DetailedWindow::DetailedWindow(IDisplayable *sensor, QList<float> *values, QWidget *parent) : QDialog(parent) {
    this->sensor = sensor;
    this->values = values;

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
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF((this->graphicsView->viewport()->width() - LEFT_OFFSET) * ratioOfTheWith + LEFT_OFFSET, this->graphicsView->viewport()->height())));

    graphicsView->setScene(scene);
    graphicsView->setBackgroundBrush(QBrush(QColor(1, 51, 50), Qt::SolidPattern));
    graphicsView->setFrameStyle(0);

    layout->addWidget(graphicsView);

    verticalLinesInterval = 1;
    verticalLinesBoldInterval = 5;
    minNumberOfHorizontalLines = 10;
    maxNumberOfHorizontalLines = 40;
    path = NULL;
    curve = NULL;
    curve2 = NULL;
    transcription = false;
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v detailnim okne v danem case
 * @brief SensorWidget::update
 * @param value hodnota
 */
void DetailedWindow::update(double value) {
    time = sensor->time;

    int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;
    int width = sensor->maxX - sensor->minX; // skutecna sirka (v jednotkach)

    int x = (time / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
    int y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);

    if (path != NULL) {
        path->lineTo(x, y); //  pridani dalsi hodnoty do path

        if (x % 3 == 0) {
            if (curve != NULL) {
                scene->removeItem(curve); // odstaneni stare krivky z grafu
                delete curve;
            }
            curve = scene->addPath(*path, QPen(Qt::white)); // pridani aktualni krivky do grafu
            //graphicsView->viewport()->repaint(); // prekresleni
        }
    }
    else {
        path = new QPainterPath(QPoint(LEFT_OFFSET, y)); // vytvoreni path s pocatecnim bodem
    }

    if (transcription) {
        if (curve2 != NULL) {
           scene->removeItem(curve2); // odstaneni stare krivky z grafu
           delete curve2;
        }
        QPainterPath path2(QPoint(x, y));
        transcriptionIndex++;
        // vykresleni krivky z minuleho zobrazeni od transcriptionIndex do konce
        int i = 0;
        double time2 = time + sensor->timeInterval;
        foreach (double value, *values) {
            i++;
            if (i <= transcriptionIndex) continue;
            x = (time2 / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
            y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);
            path2.lineTo(x, y); //  pridani dalsi hodnoty do path
            time2 += sensor->timeInterval; // pricteni casu pro dalsi hodnotu
        }
        curve2 = scene->addPath(path2, QPen(Qt::white));
    }
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v danem case bez okamziteho kresleni
 * @brief SensorWidget::updateFromFile
 * @param value
 */
void DetailedWindow::updateFromFile(float value) {
    time = sensor->time;

    int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;
    int width = sensor->maxX - sensor->minX; // skutecna sirka (v jednotkach)

    int x = (sensor->time / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
    int y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);

    if (path != NULL) {
        path->lineTo(x, y); //  pridani dalsi hodnoty do path
    }
    else {
        path = new QPainterPath(QPoint(LEFT_OFFSET, y)); // vytvoreni path s pocatecnim bodem
    }
}

/**
 * Zrusi rezim vykreslovani ze souboru a vykresli vytvorenou cestu
 * @brief DetailedWindow::cancelLoadData
 */
void DetailedWindow::cancelLoadData() {
    ratioOfTheWith = (values->size() * sensor->timeInterval) / sensor->maxX;
    if (ratioOfTheWith <= 1) {
        ratioOfTheWith = 1;
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    else {
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }
    resizeEvent(NULL);
}

/**
 * Zmena velikosti sceny pri zmene velikosti okna
 * @brief SensorWidget::resizeEvent
 * @param e
 */
void DetailedWindow::resizeEvent(QResizeEvent *) {
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF((graphicsView->viewport()->width() - LEFT_OFFSET) * ratioOfTheWith + LEFT_OFFSET, graphicsView->viewport()->height())));
    drawVerticalLines();
    drawHorizontalLines();
    drawNumbers();
    repaintGraph();
}

/**
 * Prekresli graf na aktualni sirku widgetu
 * @brief SensorWidget::repaintGraph
 */
void DetailedWindow::repaintGraph() {
    if (path != NULL) {
        if (curve != NULL) {
            scene->removeItem(curve); // odstaneni stare krivky z grafu
            delete curve;
        }
        if (curve2 != NULL){
            scene->removeItem(curve2); // odstaneni stare krivky z grafu
            delete curve2;
            curve2 = NULL;
        }
        time = 0;
        int width = sensor->maxX - sensor->minX; // skutecna sirka (v jednotkach)
        int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;
        int x, y;
        delete path;
        bool isFirst = true;
        path = new QPainterPath(QPoint(LEFT_OFFSET, 0));
        QPainterPath path2(QPoint(0, 0));

        int i = 0;
        foreach (double value, *values) {
            x = (time / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
            y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);

            if ((transcription && i <= transcriptionIndex) || !transcription) {
                path->lineTo(x, y); //  pridani dalsi hodnoty do path
            }
            else {                
                if (isFirst) path2.moveTo(x, y);
                else path2.lineTo(x, y); //  pridani dalsi hodnoty do path2
                isFirst = false;
            }
            time += sensor->timeInterval; // pricteni casu pro dalsi hodnotu
            i++;
        }

       curve = scene->addPath(*path, QPen(Qt::white));
       if (!path2.isEmpty()) {
           curve2 = scene->addPath(path2, QPen(Qt::white));
       }
       graphicsView->viewport()->repaint();
    }
}

/**
 * Odstraneni vykreslene krivky a resetovani hodnot
 * @brief SensorWidget::resetGraph
 */
void DetailedWindow::restartGraph() {
    transcription = true;
    transcriptionIndex = 0;

    time = 0;
    path = NULL;
}

/**
 * Odstraneni vykreslene krivky a resetovani hodnot
 * @brief SensorWidget::resetGraph
 */
void DetailedWindow::cleanGraph() {
    if (curve != NULL) {
        scene->removeItem(curve); // odstaneni stare krivky z grafu
        delete curve;
        curve = NULL;
    }
    if (curve2 != NULL){
        scene->removeItem(curve2); // odstaneni stare krivky z grafu
        delete curve2;
        curve2 = NULL;
    }
    sensor->time = 0;    
    delete path;
    path = NULL;
    transcription = false;
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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


