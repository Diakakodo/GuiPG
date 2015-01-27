#include "configuration.h"
#include <QFile>
#include <QDomDocument>

#ifdef _WIN32
#define DEF_GPG_EXEC "C:/Program Files (x86)/GNU/GnuPG/gpg2.exe"
#else
#define DEF_GPG_EXEC "gpg"
#endif

#define CONFIG_TAG_NAME "cfg"
#define EXEC_TAG_NAME "exec"
#define GPG_TAG_NAME "gpg"
#define PROFILE_ATTR_NAME "profile"
#define ROOT_TAG_NAME "configurations"
#define VALUE_ATTR_NAME "value"

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
    QDomDocument doc;
    if (!doc.setContent(&f)) {
        f.close();
        return false;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != ROOT_TAG_NAME) {
        f.close();
        return false;
    }
    QDomElement e = root.firstChildElement(CONFIG_TAG_NAME);
    while (!e.isNull()
           && !attrIsProfileId(e.attribute(PROFILE_ATTR_NAME), p->getId())) {
        e = e.nextSiblingElement(CONFIG_TAG_NAME);
    }
    if (!e.isNull()) {
        loadConfig(e);
    }
    f.close();
    return true;
}

QString Configuration::getGPGExecutable() const {
    return m_vars.value(GPG_TAG_NAME "/" EXEC_TAG_NAME, DEF_GPG_EXEC);
}

const Profile* Configuration::getProfile() const {
    return m_profile;
}

const QHash<QString, QString>& Configuration::getVars() const {
    return m_vars;
}

bool Configuration::save() const {
    QFile f(m_filePath);
    if (!f.open(QIODevice::WriteOnly)) {
        return false;
    }
    // TODO
    f.close();
    return true;
}

bool Configuration::attrIsProfileId(const QString& attr, unsigned id) const {
    bool ok = false;
    unsigned x = attr.toUInt(&ok);
    return ok && x == id;
}

void Configuration::loadConfig(QDomNode root, const QString& parent) {
    while (!root.isNull()) {
        if (root.isElement()) {
            QDomElement e = root.toElement();
            if (e.hasAttribute(VALUE_ATTR_NAME)) {
                m_vars.insert(parent + e.tagName(),
                              e.attribute(VALUE_ATTR_NAME));
            }
            loadConfig(e.firstChild(), parent + e.tagName() + "/");
        }
        root = root.nextSibling();
    }
}
