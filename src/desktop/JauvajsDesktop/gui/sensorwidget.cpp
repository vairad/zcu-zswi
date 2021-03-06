#include <QApplication>
#include <QGraphicsTextItem>
#include <QDebug>

#include "gui/sensorwidget.h"
#include "gui/analysiswindow.h"
#include "core/iworking.h"

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

    // propojeni signalu indikujici konec nacitani souboru s metodou, ktera pripravi widget na ziskani dat z Arduina
    //connect(((IWorking *)sensor), SIGNAL(notHaveData()), this, SLOT(cancelLoadData()));
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

    widget->setStyleSheet("QWidget#widget {background-image: url(./images/" + QString::number(sensor->ID) + ".png);"
                          "background-repeat: no-repeat;"
                          "background-position: center top;}");

    button = new QPushButton(widget);
    button->setObjectName(QStringLiteral("button"));
    button->setGeometry(QRect(100, 77, 23, 23));
    button->setText("A");
    button->setToolTip("Analyzuj");
    if (sensor->isAnalysable) {
        button->setVisible(true);
    }
    else {
        button->setVisible(false);
    }

    button2 = new QPushButton(widget);
    button2->setObjectName(QStringLiteral("button2"));
    button2->setGeometry(QRect(127, 77, 23, 23));
    //button2->setText(QApplication::translate("MainWindow", "Vyčisti", 0));

    QPixmap pixmap("./images/clean.png");
    button2->setIcon(QIcon(pixmap));
    button2->setToolTip("Vyčisti");

    label = new QLabel(widget);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(50, 20, 85, 20));
    label->setScaledContents(false);
    label->setAlignment(Qt::AlignCenter);
    label->setText(sensor->getName().toStdString().c_str());
    label->setStyleSheet("QLabel {color: #330099; font-size: 15px;}");

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
    scene->setSceneRect(QRectF(QPointF(0, 0), QPointF((this->graphicsView->width() - LEFT_OFFSET) * ratioOfTheWith + LEFT_OFFSET, this->graphicsView->height())));

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
    graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QPointF((graphicsView->viewport()->width() - LEFT_OFFSET) * ratioOfTheWith + LEFT_OFFSET, graphicsView->viewport()->height())));
    drawVerticalLines();
    drawHorizontalLines();
    drawNumbers();
    repaintGraph(); // prekresleni grafu dle sirky widgetu
}

/**
 * Prekresli graf na aktualni sirku widgetu
 * @brief SensorWidget::repaintGraph
 */
void SensorWidget::repaintGraph() {
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
        double time = sensor->time;
        sensor->time = 0;
        int width = sensor->maxX - sensor->minX; // skutecna sirka (v jednotkach)
        int height = graphicsView->viewport()->height() - BOTTOM_OFFSET;
        int x, y;
        delete path;
        bool isFirst = true;
        path = new QPainterPath(QPoint(LEFT_OFFSET, 0));
        QPainterPath path2(QPoint(0, 0));

        int i = 0;
        foreach (double value, values) {
            x = (sensor->time / (double) width) * (graphicsView->viewport()->width() - LEFT_OFFSET) + LEFT_OFFSET;
            y = graphicsView->viewport()->height() - ((value - sensor->minY) / (sensor->maxY - sensor->minY) * height + BOTTOM_OFFSET);

            if ((transcription && i <= transcriptionIndex) || !transcription) {
                path->lineTo(x, y); //  pridani dalsi hodnoty do path
            }
            else {
                if (isFirst) path2.moveTo(x, y);
                else path2.lineTo(x, y); //  pridani dalsi hodnoty do path2
                isFirst = false;

            }
            sensor->time += sensor->timeInterval; // pricteni casu pro dalsi hodnotu
            i++;
        }

       curve = scene->addPath(*path, QPen(Qt::white));
       if (!path2.isEmpty()) {
           curve2 = scene->addPath(path2, QPen(Qt::white));
       }
       graphicsView->viewport()->repaint();
       if (transcription) {
           sensor->time = time;
       }
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

    // pokud je zapnuto prepisovani, hodnota se prida do values na misto transcriptionIndex
    if (transcription) {
        if (curve2 != NULL) {
            scene->removeItem(curve2); // odstaneni stare krivky z grafu
            delete curve2;
        }
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
        restartGraph();
        detailedWindow->restartGraph();
        transcription = true;
        transcriptionIndex = 0;
    }
}

/**
 * Vykresli zadanou hodnotu do grafu (sceny) v danem case bez okamziteho kresleni
 * @brief SensorWidget::updateFromFile
 * @param value
 */
void SensorWidget::updateFromFile(float value) {
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

    values.push_back(value); // pridani hodnoty y do listu

    detailedWindow->updateFromFile(value);
    sensor->time += sensor->timeInterval; // pricteni casu pro dalsi hodnotu
}

/**
 * Resetovani hodnot
 * @brief SensorWidget::resetGraph
 */
void SensorWidget::restartGraph() {
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
    ratioOfTheWith = 1;
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    resizeEvent(NULL);
    detailedWindow->cleanGraph();
}

/**
 * Pripravi widget na nacteni a vykresleni dat ze souboru
 * Odpoji signal haveData a prepoji ke spravne metode
 * @brief SensorWidget::prepareToLoadData
 */
void SensorWidget::prepareToLoadData() {
    // odpojeni signalu indikujici ziskani dat z Arduina s metodou update2 pro vykresleni
    disconnect(sensor, SIGNAL(haveData(float)), this, SLOT(update2(float)));

    // propojeni signalu indikujici ziskani dat ze souboru s metodou updateFromFile
    connect(sensor, SIGNAL(haveData(float)), this, SLOT(updateFromFile(float)));

    cleanGraph();
}

/**
 * Zrusi rezim vykreslovani ze souboru a vykresli vytvorenou cestu
 * Odpoji signal haveData a prepoji ke spravne metode
 * @brief SensorWidget::cancelLoadData
 */
void SensorWidget::cancelLoadData() {
    // odpojeni signalu indikujici ziskani dat ze souboru s metodou updateFromFile
    disconnect(sensor, SIGNAL(haveData(float)), this, SLOT(updateFromFile(float)));

    // propojeni signalu indikujici ziskani dat z Arduina s metodou update2 pro vykresleni
    connect(sensor, SIGNAL(haveData(float)), this, SLOT(update2(float)));

    ratioOfTheWith = (values.size() * sensor->timeInterval) / sensor->maxX;
    if (ratioOfTheWith <= 1) {
        ratioOfTheWith = 1;
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    else {
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }
    resizeEvent(NULL);
    graphicsView->update();
    graphicsView->updateGeometry();
    graphicsView->viewport()->update();

    detailedWindow->cancelLoadData();
}

/**
 * Udalost na stisk Analyzuj
 * @brief SensorWidget::on_button_clicked
 */
void SensorWidget::on_button_clicked() {
    new AnalysisWindow(values, this);
}

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

