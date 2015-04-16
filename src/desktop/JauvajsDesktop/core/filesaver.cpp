#include <QFile>
#include <QTextStream>
#include <QDir>
#include "filesaver.h"

FileSaver::FileSaver() {
    FILENAME = "metadata.txt";
}

/**
 * Ulozi metadata do souboru
 * @brief FileSaver::saveMetadata
 */
void FileSaver::saveMetadata(QList<QString> data) {
    // vytvoreni slozky
    QDir dir(data[0]);
    if (!dir.exists()) {
      dir.mkdir(".");
    }

    QFile *file = new QFile(data[0]+"/"+FILENAME);
    file->open(QIODevice::WriteOnly);

    for (int i = 1; i < data.size(); i++) {
        file->write(data[i].toUtf8().constData());
        file->write(";");
    }

    file->close();
}

FileSaver::~FileSaver() {

}

