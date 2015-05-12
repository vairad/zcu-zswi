#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDateTime>
#include <QDebug>

#include "filesaver.h"

FileSaver::FileSaver(QString fileName) {
    FILE_NAME = fileName;
}

/**
 * Ulozi metadata do souboru
 * @brief FileSaver::saveMetadata
 */
void FileSaver::saveMetadata(QString folderName, QList<QString> data) {
    FOLDER_NAME = folderName;

    // vytvoreni slozky pro data
    QDir dir(FOLDER_NAME);

    if (!dir.exists()) {
      dir.mkdir(".");
    }

    // vytvoreni slozky pro uzivatele
    QDir dir2(FOLDER_NAME + "/" + data[0]);
    if (!dir2.exists()) {
      dir2.mkdir(".");
    }

    QFile *file = new QFile(FOLDER_NAME + "/" + data[0] + "/" + FILE_NAME);
    file->open(QIODevice::WriteOnly);

    for (int i = 1; i < data.size(); i++) {
        file->write(data[i].toUtf8().constData());
        file->write(";");
    }

    file->close();
    delete file;
}

/**
 * Vytvori soubor pro ukladani dat ze senzoru
 * Nazev je vytvoren z aktualniho data a casu
 * @brief FileSaver::createFileForData
 * @param username uzivatelske jmeno (slozka)
 */
void FileSaver::createFileForData(QString username) {
    file = new QFile(FOLDER_NAME + "/" + username + "/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".csv");
    file->open(QIODevice::WriteOnly);
}

/**
 * Ulozi radek zaznamu ze senzoru do souboru
 * @brief FileSaver::saveData
 * @param data radek
 */
void FileSaver::saveData(float data[]) {
    if (file->isOpen()) {
        for (int i = 0; i < 7; i++) {
            file->write(QString::number(data[i]).toUtf8().constData());
            file->write(";");
        }
        file->write("\n");
    }
}

/**
 * Zavre soubor pro ukladani dat ze senzoru
 * @brief FileSaver::closeFileForData
 */
void FileSaver::closeFileForData() {
    file->close();
}

FileSaver::~FileSaver() {
    if(file->isOpen()){
        file->close();
    }
    delete file;
}

