#include "profile.h"
#include <QStandardPaths>

#ifdef _WIN32
#define DEFAULT_EXEC "C:/Program Files (x86)/GNU/GnuPG/gpg2.exe"
#define DEFAULT_PATH QStandardPaths::displayName(QStandardPaths::HomeLocation)\
    + "/AppData/Roaming/gnupg/"
#else
#define DEFAULT_EXEC "gpg"
#define DEFAULT_PATH "~/.gnupg/"
#endif

Profile::Profile(unsigned id, const QString& name) : m_id(id), m_name(name),
    m_exec(DEFAULT_EXEC), m_path(DEFAULT_PATH) {
    m_isDefault = 0;
}

unsigned Profile::getId() const {
    return m_id;
}

const QString& Profile::getName() const {
    return m_name;
}

const QString& Profile::getGPGExecutable() const {
    return m_exec;
}

unsigned Profile::isDefault() const {
    return m_isDefault;
}

void Profile::setGPGExecutable(const QString& exec) {
    m_exec = exec;
}

const QString& Profile::getConfigurationPath() const {
    return m_path;
}

void Profile::setConfigurationPath(const QString& path) {
    m_path = path;
}

void Profile::setDefault(unsigned isDefault) {
    if (isDefault > 1) {
        // TODO: balancer une exception
        return;
    }
    m_isDefault = isDefault;
}
