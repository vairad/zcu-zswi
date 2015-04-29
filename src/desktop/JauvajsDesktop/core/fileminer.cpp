#include <QString>
#include <QFile>
#include <QTextStream>
#include <QException>

#include <QDebug>

#include "core/fileminer.h"
#include "core/fileproblemexception.h"

FileMiner::FileMiner(QString fileName){
    sourceFile.setFileName(fileName);
    opened = sourceFile.open(QIODevice::ReadOnly);

    if(opened){
        in = new QTextStream(&sourceFile);
    }else{
        throw FileOpenProblemException(fileName);
    }
}

FileMiner::~FileMiner(){
}

void FileMiner::sendMessage(QString line){
    //class only read file no implementation
    line.clear();
}

QString FileMiner::getLastIncoming(){

    if(opened && !in->atEnd()){
       // qDebug() << "read line";
        QString line = in->readLine();
       // qDebug() << line;
        return line;
    }

    if(opened && in->atEnd()){
        qDebug() << "close file";
        opened = false;
        delete in; // free memory of data stream
        sourceFile.close();
    }
   // qDebug() << "read NOline";
    return NULL;
}

