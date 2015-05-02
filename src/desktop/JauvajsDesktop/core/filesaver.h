#ifndef FILESAVER_H
#define FILESAVER_H

#include <QString>

#include "core/istorable.h"

/**
 * Uklada data do souboru
 * @brief The FileSaver class
 */
class FileSaver : public IStorable {
public:
    FileSaver(QString fileName);
    ~FileSaver();
    void saveMetadata(QString folderName, QList<QString> data);
    void createFileForData(QString username);
    void saveData(float data[]);
    void closeFileForData();
    /** nazev slozky pro ukladani dat */
    QString FOLDER_NAME;
    /** nazev souboru pro ulozeni metadat */
    QString FILENAME;

private:
    /** soubor pro data */
    QFile *file;

};

#endif // FILESAVER_H
