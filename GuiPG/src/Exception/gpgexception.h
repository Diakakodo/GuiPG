#ifndef GPGEXCEPTION
#define GPGEXCEPTION

#include <QException>
#include <QString>

class GPGException : QException {
    private:
        QString m_msg;

    public:
        virtual ~GPGException();
        virtual const char* what() const throw = 0;
        virtual void raise() const = 0;
        virtual GPGException* clone() const;
};

#endif // GPGEXCEPTION

