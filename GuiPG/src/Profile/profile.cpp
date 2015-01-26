#include "profile.h"

Profile::Profile(unsigned id, const QString& name) : m_id(id), m_name(name) {

}

unsigned Profile::getId() const {
    return m_id;
}

const QString& Profile::getName() const {
    return m_name;
}
