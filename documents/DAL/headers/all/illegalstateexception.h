#ifndef ILLEGALSTATEEXCEPTION_H
#define ILLEGALSTATEEXCEPTION_H

#include <QException>
#include <QString>

class IllegalStateException : public QException
{
    public:
        explicit IllegalStateException(QString msg = "");
        const char* what() const throw();
    void raise() const;
    IllegalStateException *clone() const;
    private:
        QString m_msg;
};

#endif // ILLEGALSTATEEXCEPTION_H


