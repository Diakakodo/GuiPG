
#include "illegalargumentexception.h"


IllegalArgumentException::IllegalArgumentException(QString msg)
    : m_msg(msg) {

}

const char* IllegalArgumentException::what() const throw() {
  return m_msg.toLatin1();
}

void IllegalArgumentException::raise() const {
    throw *this;
}

IllegalArgumentException* IllegalArgumentException::clone() const {
    return new IllegalArgumentException(*this);
}

