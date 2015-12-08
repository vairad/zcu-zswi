#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <QString>
#include <QException>

class FileOpenProblemException : public QException{
        QString message;
    public:
        void raise() const;
        FileOpenProblemException *clone() const;

        QString getMessage();

        FileOpenProblemException();
        FileOpenProblemException(QString fileName);
        ~FileOpenProblemException() throw();
};

#endif // FILENOTFOUNDEXCEPTION_H
