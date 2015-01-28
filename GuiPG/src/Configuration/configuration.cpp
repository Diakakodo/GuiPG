#include "configuration.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

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
    m_profile = p;
    QFile f(m_filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        initConfig();
        return false;
    }
    if (!m_doc.setContent(&f)) {
        initConfig();
        f.close();
        return false;
    }

    QDomElement root = m_doc.documentElement();
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
        m_profileElement = e;
        loadConfig(e.firstChild());
    }
    f.close();
    return true;
}

QString Configuration::getGPGExecutable() const {
    QDomElement e = m_vars.value(GPG_TAG_NAME "/" EXEC_TAG_NAME);
    return e.isNull() ? DEF_GPG_EXEC : e.attribute(VALUE_ATTR_NAME);
}

const Profile* Configuration::getProfile() const {
    return m_profile;
}

const QHash<QString, QDomElement>& Configuration::getVars() const {
    return m_vars;
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

void Configuration::setGPGExecutable(const QString& path) {
    QDomElement e = m_vars.value(GPG_TAG_NAME "/" EXEC_TAG_NAME);
    if (e.isNull()) {
        QDomElement gpg = m_profileElement.firstChildElement(GPG_TAG_NAME);
        if (gpg.isNull()) {
            gpg = m_doc.createElement(GPG_TAG_NAME);
            m_profileElement.appendChild(gpg);
        }
        e = m_doc.createElement(EXEC_TAG_NAME);
        gpg.appendChild(e);
        m_vars.insert(GPG_TAG_NAME "/" EXEC_TAG_NAME, e);
    }
    e.setAttribute(VALUE_ATTR_NAME, path);
}

bool Configuration::attrIsProfileId(const QString& attr, unsigned id) const {
    bool ok = false;
    unsigned x = attr.toUInt(&ok);
    return ok && x == id;
}

void Configuration::initConfig() {
    QDomElement root = m_doc.createElement(ROOT_TAG_NAME);
    m_profileElement = m_doc.createElement(CONFIG_TAG_NAME);
    m_profileElement.setAttribute(PROFILE_ATTR_NAME, m_profile->getId());
    m_doc.appendChild(root);
    root.appendChild(m_profileElement);
}

void Configuration::loadConfig(QDomNode root, const QString& parent) {
    while (!root.isNull()) {
        if (root.isElement()) {
            QDomElement e = root.toElement();
            if (e.hasAttribute(VALUE_ATTR_NAME)) {
                m_vars.insert(parent + e.tagName(), e);
            }
            loadConfig(e.firstChild(), parent + e.tagName() + "/");
        }
        root = root.nextSibling();
    }
}
