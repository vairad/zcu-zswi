#include "loadfile.h"
#include "graph.h"

/**
 * Simuluje ziskavani dat z e-health
 * @brief LoadFile::LoadFile
 * @param g
 */
LoadFile::LoadFile(Graph *g) : g(g) {
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
        i++;
    }

    fclose(f);
}

LoadFile::~LoadFile() {

}

