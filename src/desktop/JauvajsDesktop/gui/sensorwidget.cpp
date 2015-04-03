#include "gui/sensorwidget.h"
#include <QApplication>
#include "loadfile.h"
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
 * Vykresli popisy grafu
 * @brief SensorWidget::drawNumbers
 */
void SensorWidget::drawNumbers() {
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
void SensorWidget::drawVerticalLines() {
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
void SensorWidget::drawHorizontalLines() {
    int numberOfLines; // pocet car
    double interval; // interval car
    int boldInterval = 4; // interval tucnych car
    int width = 1500;
    int height = sensor->maxY - sensor->minY; // skutecna vyska
    numberOfLines = height;
    while (numberOfLines < 6) {
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

