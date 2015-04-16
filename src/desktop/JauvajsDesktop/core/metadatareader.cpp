#include <QDir>
#include <QFile>
#include <QTextStream>
#include "metadatareader.h"

MetadataReader::MetadataReader() {
    FILENAME = "metadata.txt";
}

/**
 * Nacte metadata do listu
 * @brief MetadataReader::loadMetadata
 * @param username uzivatelske jmeno
 * @return QList metadat
 */
QList<QString> MetadataReader::loadMetadata(QString username) {
    // nalezeni slozky
    QDir dir(username);
    if (!dir.exists()) {
      return QList<QString>();
    }

    QFile *file = new QFile(username+"/"+FILENAME);
    file->open(QIODevice::ReadOnly);

    QTextStream in(file);
    in.setCodec("UTF-8");
    QString line = in.readLine();
    return line.split(';');

    file->close();
}

MetadataReader::~MetadataReader() {

}

