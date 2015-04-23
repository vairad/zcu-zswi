#include <QFile>
#include <QTextStream>
#include <QDir>
#include "filesaver.h"

FileSaver::FileSaver(QString fileName) {
    FILENAME = fileName;
}

/**
 * Ulozi metadata do souboru
 * @brief FileSaver::saveMetadata
 */
void FileSaver::saveMetadata(QString folderName, QList<QString> data) {
    FOLDER_NAME = folderName;

    // vytvoreni slozky pro data
    QDir dir(FOLDER_NAME);

    if (!dir.exists()) {
      dir.mkdir(".");
    }

    // vytvoreni slozky pro uzivatele
    QDir dir2(FOLDER_NAME + "/" + data[0]);
    if (!dir2.exists()) {
      dir2.mkdir(".");
    }

    QFile *file = new QFile(FOLDER_NAME + "/" + data[0] + "/" + FILENAME);
    file->open(QIODevice::WriteOnly);

    for (int i = 1; i < data.size(); i++) {
        file->write(data[i].toUtf8().constData());
        file->write(";");
    }

    file->close();
}

FileSaver::~FileSaver() {

}

