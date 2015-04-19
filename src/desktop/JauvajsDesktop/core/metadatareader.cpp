#include <QDir>
#include <QFile>
#include <QTextStream>
#include "metadatareader.h"

MetadataReader::MetadataReader(QString folderName, QString fileName) {
    FOLDER_NAME = folderName;
    FILENAME = fileName;
}

/**
 * Nacte metadata do listu
 * @brief MetadataReader::loadMetadata
 * @param username uzivatelske jmeno
 * @return QList metadat
 */
QList<QString> MetadataReader::loadMetadata(QString username) {
    // nalezeni slozky
    QDir dir(FOLDER_NAME + "/" + username);
    if (!dir.exists()) {
      return QList<QString>();
    }

    QFile *file = new QFile(FOLDER_NAME + "/" + username + "/" + FILENAME);
    file->open(QIODevice::ReadOnly);

    QTextStream in(file);
    in.setCodec("UTF-8");
    QString line = in.readLine();
    return line.split(';');

    file->close();
}

MetadataReader::~MetadataReader() {

}
