#include "configuration.h"
#include <QFile>
#include <QDomDocument>

Configuration::Configuration(const QString& filePath)
    : m_filePath(filePath), m_profile(nullptr) {

}

bool Configuration::isLoaded() const {
    return m_profile != nullptr;
}

bool Configuration::load(const Profile* p) {
    QFile f(m_filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        return false;
    }
    if (!m_doc.setContent(&f)) {
        f.close();
        return false;
    }
    // TODO : charger les différentes variables
    f.close();
    return true;
}

const Profile* Configuration::getProfile() const {
    return m_profile;
}

bool Configuration::save() {
    QFile f(m_filePath);
    if (!f.open(QIODevice::WriteOnly)) {
        return false;
    }
    QTextStream out(&f);
    out << m_doc.toString();
    f.close();
    return true;
}
