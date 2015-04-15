#include "graphdescription.h"

GraphDescription::GraphDescription() {
    itemsExist = false;
}

/**
 * Vykresli popisy grafu
 * @brief SensorWidget::drawNumbers
 */
void GraphDescription::drawNumbers() {
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
    textMaxY = scene->addText(QString::number(sensor->maxY) + " " + sensor->unit, font);
    textMaxY->setPos(0,0);
    textMaxY->setDefaultTextColor(Qt::white);

    // popis nejmensi hodnoty Y
    textMinY = scene->addText(QString::number(sensor->minY), font);
    textMinY->setPos(0, graphicsView->viewport()->height() - textMinY->boundingRect().height() - BOTTOM_OFFSET);
    textMinY->setDefaultTextColor(Qt::white);

    // popis nejvyssi hodnoty X
    textMaxX = scene->addText(QString::number(sensor->maxX) + " s [time]", font);
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
void GraphDescription::drawVerticalLines() {
    // odebrani starych hodnot
    foreach (QGraphicsLineItem *item, lineList) {
        scene->removeItem(item);
    }
    lineList.clear();

    int width = sensor->maxX - sensor->minX; // skutecna sirka (v jednotkach)
    double numberOfLines = width / (double) verticalLinesInterval;
    double interval = (graphicsView->viewport()->width() - LEFT_OFFSET) / numberOfLines; // interval v px

    for (int i = 1; i <= numberOfLines; i++) {
        if (i != 0)
        if (i % verticalLinesBoldInterval == 0) {
            QPen pen;
            pen.setWidth(2);
            pen.setBrush(QColor(0, 102, 96));
            lineList.push_back(scene->addLine(LEFT_OFFSET + i*interval, 0, LEFT_OFFSET + i*interval, graphicsView->viewport()->height(), pen));
        }
        else {
            lineList.push_back(scene->addLine(LEFT_OFFSET + i*interval, 0, LEFT_OFFSET + i*interval, graphicsView->viewport()->height(), QPen(QColor(0, 102, 96))));
        }
    }
}

/**
 * Vykresli horizontalni cary pro lepsi orientaci v grafu
 * @brief SensorWidget::drawVerticalLines
 */
void GraphDescription::drawHorizontalLines() {
    int numberOfLines; // pocet car
    double interval; // interval horizontalich car
    int boldInterval = 4; // interval tucnych car

    int height = sensor->maxY - sensor->minY; // skutecna vyska
    int pxHeight = graphicsView->viewport()->height() - BOTTOM_OFFSET;// vyska v pixelech
    numberOfLines = height;
    // zvysovani poctu car dokud jich je min nez minNumberOfHorizontalLines
    while (numberOfLines < minNumberOfHorizontalLines) {
        numberOfLines *= 2;
    }
    // snizovani poctu car dokud jich je vic nez maxNumberOfHorizontalLines
    while (numberOfLines > maxNumberOfHorizontalLines) {
        // pokud neni zadny zbytek po deleni 2, provedeme deleni 2
        if (numberOfLines % 2 == 0) {
            numberOfLines /= 2;
        }
        // pokud je zbytek, pokusime se delit maxNumberOfHorizontalLines
        else {
            numberOfLines = height;
            while (numberOfLines > maxNumberOfHorizontalLines) {
                numberOfLines /= maxNumberOfHorizontalLines;
            }
            break;
        }
    }

    interval = (graphicsView->viewport()->height() - BOTTOM_OFFSET) / (double) numberOfLines;
    for (int i = 1; i < numberOfLines; i++) {
        if (i % (boldInterval + 1) == 0) {
            QPen pen;
            pen.setWidth(2);
            pen.setBrush(QColor(0, 102, 96));
            scene->addLine(0, pxHeight - (int) i * interval, WIDTH, pxHeight - (int) i * interval, pen);
        }
        else {
            scene->addLine(0, pxHeight - (int) i * interval, WIDTH, pxHeight - (int) i * interval, QPen(QColor(0, 102, 96)));
        }
    }
}

GraphDescription::~GraphDescription() {

}

