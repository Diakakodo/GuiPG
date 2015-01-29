#include "configuration.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <iostream>

#ifdef _WIN32
#define DEF_GPG_EXEC "C:/Program Files (x86)/GNU/GnuPG/gpg2.exe"
#else
#define DEF_GPG_EXEC "gpg"
#endif

#define EXEC_TAG_NAME "exec"
#define GPG_TAG_NAME "gpg"
#define ID_ATTR_NAME "id"
#define NAME_ATTR_NAME "name"
#define PROFILE_TAG_NAME "profile"
#define ROOT_TAG_NAME "configurations"
#define VALUE_ATTR_NAME "value"

using namespace std;

Configuration::Configuration(const QString& filePath)
    : m_filePath(filePath) {
}

//TODO
bool Configuration::load() {
    return false;
}

const QList<Profile*>& Configuration::getProfiles() const {
    return m_profiles;
}

//TODO
bool Configuration::save() {
    return false;
}
