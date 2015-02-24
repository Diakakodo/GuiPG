
#include "gpgexception.h"


GPGException::GPGException(QString msg) : m_msg(msg) {

}

const char* GPGException::what() {
    return m_msg.toLatin1();
}

void GPGException::raise() const {
    throw *this;
}

