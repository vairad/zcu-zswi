#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsView>

class Graph
{
    QGraphicsView *graphicsView;
    int minX;
    int maxX;
    int minY;
    int maxY;

    int time;
    int lastY;
public:
    Graph(QGraphicsView *graphicsView);
    void update(double value);
    ~Graph();
};

#endif // GRAPH_H
