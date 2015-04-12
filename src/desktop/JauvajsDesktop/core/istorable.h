#ifndef ISTORABLE_H
#define ISTORABLE_H

#include <vector>
#include <QString>
#include <QList>

/**
 * Exportuje data z aplikace
 * @brief The IStorable class
 */
class IStorable {
public:
    /**
     * Ulozi metadata do souboru
     * @brief saveMetadata
     * @param data list dat
     */
    virtual void saveMetadata(QList<QString> data) = 0;
};

#endif // ISTORABLE_H
