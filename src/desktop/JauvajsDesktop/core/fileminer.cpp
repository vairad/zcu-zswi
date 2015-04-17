#include "fileminer.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QException>

//#include <QDebug>


FileMiner::FileMiner(QString fileName){
    sourceFile.setFileName(fileName);
    opened = sourceFile.open(QIODevice::ReadOnly);

    if(opened){
        in = new QTextStream(&sourceFile);
    }else{
        throw new QException();
    }
}

FileMiner::~FileMiner(){
    sourceFile.close();
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
   // qDebug() << "read NOline";
    return NULL;
}

