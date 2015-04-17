#include "loadfile.h"
#include "gui/mainwindow.h"
#include "core/fileminer.h"



LoadFile::LoadFile(SensorWidget *g) : g(g) {
    run();
}

/**
 * Nacte soubor a spusti vykresleni dat
 * @brief LoadFile::run
 */
void LoadFile::run2() {
    FILE *f;
    float value = 0;

    f = fopen("ekg.dat", "r");
    if (f == NULL) printf("chyba pri nacitani souboru\n");


    int i = 0;

    while (fscanf(f, "%f", &value) == 1 /*&& i<500*/) {
        g->update(value);
        //printf("%d\n", i);
        i++;
    }

    fclose(f);
}

/**
 * Nacte soubor a spusti vykresleni dat
 * @brief LoadFile::run
 */
void LoadFile::run() {

    try{
        FileMiner miner("ekg.dat");

        //qDebug() << "miner loaded \n";

        QString line = miner.getLastIncoming(); //read last line from miner OR NULL
        while (line != NULL){
            g->update(line.toDouble()); //this line is not possible for Arduino data

            line = miner.getLastIncoming();
        }
    }catch(QException &e){
        //handle exception caused
    }

}

void LoadFile::setGraph(SensorWidget *g) {
    this->g = g;
}

void LoadFile::setScene(QGraphicsScene *s) {
    this->s = s;
}

LoadFile::~LoadFile() {

}

