#ifndef FILESAVER_H
#define FILESAVER_H

#include <QString>
#include "istorable.h"

/**
 * Uklada data do souboru
 * @brief The FileSaver class
 */
class FileSaver : public IStorable {
public:
    FileSaver(QString folderName, QString fileName);
    ~FileSaver();
    void saveMetadata(QList<QString> data);
    /** nazev slozky pro ukladani dat */
    QString FOLDER_NAME;
    /** nazev souboru pro ulozeni metadat */
    QString FILENAME;

};

#endif // FILESAVER_H
