#include "graph.h"

Graph::Graph(QGraphicsView *graphicsView): graphicsView(graphicsView) {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 200;

    time = 0;
    lastY = -1;

    this->graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QPointF(this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height())));

    this->graphicsView->setBackgroundBrush(QBrush(QColor(48, 128, 20), Qt::SolidPattern));
    this->graphicsView->setFrameStyle(0);
    //this->graphicsView->scene()->addText("text");
}

/**
 * Vykresli zadanou hodnotu do grafu v danem case
 * @brief Graph::update
 * @param value
 */
void Graph::update(double value) {
    int y = graphicsView->viewport()->height() - ((value - minY) / (maxY - minY) * graphicsView->viewport()->height());
    //printf("%d\n", y);
    if (lastY != -1) {
        graphicsView->scene()->addLine(time, lastY, time+1, y, QPen(Qt::white));
        graphicsView->viewport()->repaint();
    }

    lastY = y;
    time++;
}

Graph::~Graph() {

}

