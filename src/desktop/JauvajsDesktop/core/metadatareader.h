#ifndef METADATAREADER_H
#define METADATAREADER_H

#include <QString>

/**
 * Nacita metadata ze souboru
 * @brief The MetadataReader class
 */
class MetadataReader {
public:
    MetadataReader(QString folderName, QString fileName);
    ~MetadataReader();
    QList<QString> loadMetadata(QString username);
    /** nazev slozky pro ukladani dat */
    QString FOLDER_NAME;
    /** nazev souboru pro nacteni metadat */
    QString FILENAME;
};

#endif // METADATAREADER_H
