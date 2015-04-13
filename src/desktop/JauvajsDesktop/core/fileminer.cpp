#include "fileminer.h"

#include <QString>
#include <QFile>

#define LINE_SIZE_BUFFER 255

FileMiner::FileMiner(QString fileName){
    sourceFile.setFileName(fileName);
    opened = sourceFile.open(QIODevice::ReadOnly);
}

FileMiner::~FileMiner(){
    sourceFile.close();
}

void FileMiner::sendMessage(QString line){
    //class only read file no implementation
    line.clear();
}

QString FileMiner::getLastIncoming(){
    char buffer[LINE_SIZE_BUFFER];

    if(opened && sourceFile.canReadLine()){
        sourceFile.readLine(buffer, LINE_SIZE_BUFFER);
        return QString(buffer);

    }else{
        return NULL;

    }
}

