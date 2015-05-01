#ifndef METADATAREADER_H
#define METADATAREADER_H

#include <QString>

/**
 * Nacita metadata ze souboru
 * @brief The MetadataReader class
 */
class MetadataReader {
public:
    MetadataReader(QString fileName);
    ~MetadataReader();
    QList<QString> loadMetadata(QString folderName, QString username);
    /** nazev slozky pro ukladani dat */
    QString FOLDER_NAME;
    /** nazev souboru pro nacteni metadat */
    QString FILENAME;
    /** pocet metadat */
    static const int NUMBER_OF_METADATA = 15;
};

#endif // METADATAREADER_H
