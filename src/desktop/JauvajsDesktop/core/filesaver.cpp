#include <QFile>
#include <QTextStream>
#include <iostream>
#include "filesaver.h"

FileSaver::FileSaver() {
    FILENAME = "metadata.txt";
}

/**
 * Ulozi metadata do souboru
 * @brief FileSaver::saveMetadata
 */
void FileSaver::saveMetadata(QList<QString> data) {
    QFile *file = new QFile(FILENAME);
    file->open(QIODevice::WriteOnly);

    for (int i = 0; i < data.size(); i++) {
        file->write(data[i].toUtf8().constData());
        file->write(";");
    }

    file->close();
}

FileSaver::~FileSaver() {

}

