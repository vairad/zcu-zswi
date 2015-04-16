#ifndef METADATAREADER_H
#define METADATAREADER_H

#include <QString>

/**
 * Nacita metadata ze souboru
 * @brief The MetadataReader class
 */
class MetadataReader {
public:
    MetadataReader();
    ~MetadataReader();
    QList<QString> loadMetadata(QString username);
    /** nazev souboru pro nacteni metadat */
    QString FILENAME;
};

#endif // METADATAREADER_H
