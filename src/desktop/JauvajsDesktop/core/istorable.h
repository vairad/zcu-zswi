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
     * @param folderName
     * @param data list dat
     */
    virtual void saveMetadata(QString folderName, QList<QString> data) = 0;
    /**
     * Ulozi jeden radek dat do souboru
     * @brief saveData
     * @param data radek
     */
    virtual void saveData(float data[], int data_count) = 0;
    /**
     * Vytvori soubor pro ukladani dat ze senzoru
     * Nazev je vytvoren z aktualniho data a casu
     * @brief createFileForData
     * @param username uzivatelske jmeno (slozka)
     */
    virtual void createFileForData(QString username, QList<QString> header, int data_count) = 0;

    /**
     * Zavre soubor pro ukladani dat ze senzoru
     * @brief closeFileForData
     */
    virtual void closeFileForData() = 0;
};

#endif // ISTORABLE_H
