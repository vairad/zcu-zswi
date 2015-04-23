#ifndef FILESAVER_H
#define FILESAVER_H

#include "core/istorable.h"

#include <QString>

/**
 * Uklada data do souboru
 * @brief The FileSaver class
 */
class FileSaver : public IStorable {
public:
    FileSaver(QString fileName);
    ~FileSaver();
    void saveMetadata(QString folderName, QList<QString> data);
    /** nazev slozky pro ukladani dat */
    QString FOLDER_NAME;
    /** nazev souboru pro ulozeni metadat */
    QString FILENAME;

};

#endif // FILESAVER_H
