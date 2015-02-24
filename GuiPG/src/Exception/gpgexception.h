#ifndef GPGEXCEPTION
#define GPGEXCEPTION

#include <QException>
#include <QString>

class GPGException : QException {
    protected:
        QString m_msg;
    public:
        GPGException(QString msg = "");
        const char* what();
        void raise() const;
};

#endif // GPGEXCEPTION

