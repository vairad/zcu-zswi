#include <QApplication>
#include <QGraphicsTextItem>
#include <QDebug>

#include "gui/sensorwidget.h"

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
    maxNumberOfHorizontalLines = 20;

    detailedWindow = new DetailedWindow(sensor, &values);
    path = NULL;
    curve = NULL;
    curve2 = NULL;
    transcription = false;

    // propojeni signalu indikujici ziskani dat z Arduina s metodou update2 pro vykresleni
    connect(sensor, SIGNAL(haveData(float)), this, SLOT(update2(float)));
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

    //button = new QPushButton(widget);
    //button->setObjectName(QStringLiteral("button"));
    //button->setGeometry(QRect(10, 50, 131, 23));
    //button->setText(QApplication::translate("MainWindow", "Zah\303\241jit z\303\241znam", 0));

    button2 = new QPushButton(widget);
    button2->setObjectName(QStringLiteral("button2"));
    button2->setGeometry(QRect(10, 75, 131, 23));
    button2->setText(QApplication::translate("MainWindow", "Vyčisti", 0));

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
void SensorWidget::resizeEvent(QResizeEvent *) {
    graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QPointF(graphicsView->viewport()->width(), graphicsView->viewport()->height())));
    drawVerticalLines();
    drawNumbers();
    repaintGraph(); // prekresleni grafu dle sirky widgetu
}

/**
 * Prekresli graf na aktualni sirku widgetu
 * @brief SensorWidget::repaintGraph
 */
void SensorWidget::repaintGraph() {
    if (path != NULL) {
        if (curve != NULL) scene->removeItem(curve); // odstaneni stare krivky z grafu
        if (curve2 != NULL){
            scene->removeItem(curve2); // odstaneni stare krivky z grafu
            curve2 = NULL;
        }
        sensor->time = 0;
        int width = sensor->maxX - sensor->minX; // skutecna sirka (v jednotkach)
        int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;
        int x, y;
        QPainterPath path(QPoint(LEFT_OFFSET, 0));

        foreach (double value, values) {
            x = (sensor->time / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
            y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);
            path.lineTo(x, y); //  pridani dalsi hodnoty do path
            sensor->time += sensor->timeInterval; // pricteni casu pro dalsi hodnotu
        }

       curve = scene->addPath(path, QPen(Qt::white));
       graphicsView->viewport()->repaint();
    }
}

/**
 * Reakce na kliknuti do grafu
 * @brief mousePressEvent
 * @param event
 */
void SensorWidget::mousePressEvent(QMouseEvent *) {
    detailedWindow->showNormal();
    detailedWindow->raise();
    QApplication::setActiveWindow(detailedWindow);
}

/**
 * Pocatecni nastaveni velikosti sceny
 * @brief SensorWidget::setUp
 */
void SensorWidget::setUp() {
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF(this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height())));
    drawVerticalLines();
    drawHorizontalLines();
    drawNumbers();

    if (!isVisible) {
        hide();
        action1->setChecked(false);
    }
    else {
        show();
        action1->setChecked(true);
    }

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
        resizeEvent(NULL);
    }
    else {
        this->hide();
        action1->setChecked(false);
        visible(false);
        resizeEvent(NULL);
    }
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v danem case
 * @brief SensorWidget::update
 * @param value
 */
void SensorWidget::update2(float value) {
    if (value != value) return;

    int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;
    int width = sensor->maxX - sensor->minX; // skutecna sirka (v jednotkach)

    int x = (sensor->time / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
    int y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);

    if (path != NULL) {
        path->lineTo(x, y); //  pridani dalsi hodnoty do path

        if (x % 3 == 0) {
            if (curve != NULL) scene->removeItem(curve); // odstaneni stare krivky z grafu
            curve = scene->addPath(*path, QPen(Qt::white)); // pridani aktualni krivky do grafu
            //graphicsView->viewport()->repaint(); // prekresleni
        }

    }
    else {
        path = new QPainterPath(QPoint(LEFT_OFFSET, y)); // vytvoreni path s pocatecnim bodem
    }

    // pokud je zapnuto prepisovani, hodnota se prida do values na misto transcriptionIndex
    if (transcription) {
        if (curve2 != NULL) scene->removeItem(curve2); // odstaneni stare krivky z grafu
        QPainterPath path2(QPoint(x, y));
        values.replace(transcriptionIndex, value); // pridani hodnoty na misto transcriptionIndex
        transcriptionIndex++;
        // vykresleni krivky z minuleho zobrazeni od transcriptionIndex do konce
        int i = 0;
        double time2 = sensor->time + sensor->timeInterval;
        foreach (double value, values) {
            i++;
            if (i <= transcriptionIndex) continue;
            x = (time2 / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
            y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);
            path2.lineTo(x, y); //  pridani dalsi hodnoty do path
            time2 += sensor->timeInterval; // pricteni casu pro dalsi hodnotu
        }
        curve2 = scene->addPath(path2, QPen(Qt::white));
    }
    // pokud se neprepisuje, hodota je pridana na konec values
    else {
        values.push_back(value); // pridani hodnoty y do listu
    }

    detailedWindow->update(value); // kresleni do detailniho okna
    sensor->time += sensor->timeInterval; // pricteni casu pro dalsi hodnotu

    // pokud graf dobehne do konce platna, je zapnuto prepisovani od zacatku platna
    if (sensor->time > sensor->maxX) {
        resetGraph();
        detailedWindow->resetGraph();
        transcription = true;
        transcriptionIndex = 0;
    }
}

/**
 * Resetovani hodnot
 * @brief SensorWidget::resetGraph
 */
void SensorWidget::resetGraph() {
    sensor->time = 0;
    delete path;
    path = NULL;
}

/**
 * Odstraneni vykreslene krivky a resetovani hodnot
 * @brief SensorWidget::resetGraph
 */
void SensorWidget::cleanGraph() {
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
    values.clear();
    detailedWindow->cleanGraph();
}

/**
 * Udalost na stisk Zahajit zaznam
 * @brief SensorWidget::on_button_clicked
 */
//void SensorWidget::on_button_clicked() {
//    manager->draw = true;
//}

/**
 * Udalost na stisk Vyčisti
 * @brief SensorWidget::on_button_clicked
 */
void SensorWidget::on_button2_clicked() {
    cleanGraph();
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

