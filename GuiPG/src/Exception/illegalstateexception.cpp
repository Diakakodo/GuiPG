#include "illegalstateexception.h"

IllegalStateException::IllegalStateException(QString msg)
    : m_msg(msg) {

}

const char* IllegalStateException::what() const throw() {
  return m_msg.toLatin1();
}

void IllegalStateException::raise() const {
    throw *this;
}

IllegalStateException* IllegalStateException::clone() const {
    return new IllegalStateException(*this);
}

