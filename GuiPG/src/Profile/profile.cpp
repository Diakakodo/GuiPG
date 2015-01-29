#include "profile.h"

Profile::Profile(unsigned id, const QString& name, const QString& exec)
    : m_id(id), m_name(name), m_exec(exec) {

}

unsigned Profile::getId() const {
    return m_id;
}

const QString& Profile::getName() const {
    return m_name;
}

QString Configuration::getGPGExecutable() const {
    return m_exec;
}

void Configuration::setGPGExecutable(const QString& exec) {
    m_exec = exec;
}
