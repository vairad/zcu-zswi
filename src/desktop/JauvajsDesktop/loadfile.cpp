#include "loadfile.h"
#include "gui/mainwindow.h"

LoadFile::LoadFile(SensorWidget *g) : g(g) {
    run();
}

/**
 * Nacte soubor a spusti vykresleni dat
 * @brief LoadFile::run
 */
void LoadFile::run() {
    FILE *f;
    float value = 0;

    f = fopen("ekg.dat", "r");
    if (f == NULL) printf("chyba pri nacitani souboru\n");


    int i = 0;

    while (fscanf(f, "%f", &value) == 1 && i<500) {
        g->update(value);
        //printf("%d\n", i);
        i++;
    }

    fclose(f);
}

void LoadFile::setGraph(SensorWidget *g) {
    this->g = g;
}

void LoadFile::setScene(QGraphicsScene *s) {
    this->s = s;
}

LoadFile::~LoadFile() {

}

