#ifndef LOADFILE_H
#define LOADFILE_H

#include <QtCore>
#include "graph.h"

class LoadFile {
public:
    LoadFile(Graph *g);
    ~LoadFile();
    void run();

private:
    Graph *g;
};

#endif // LOADFILE_H
