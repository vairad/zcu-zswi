#include <QString>
//#include <QDebug>

#include "fileproblemexception.h"

FileOpenProblemException::FileOpenProblemException() {
    message = "No message was added.";
}

FileOpenProblemException::FileOpenProblemException(QString fileName) {
    this->message = "Nebylo možné otevřít soubor "+fileName;
   // qDebug() << message;
}

void FileOpenProblemException::raise() const {
    throw *this;
}

FileOpenProblemException *FileOpenProblemException::clone() const {
    return new FileOpenProblemException(*this);
}

QString FileOpenProblemException::getMessage(){
    return message;
}

FileOpenProblemException::~FileOpenProblemException() throw() {
    //delete &message;
}

