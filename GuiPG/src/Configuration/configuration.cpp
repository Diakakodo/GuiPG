#include "configuration.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <iostream>

#define EXEC_TAG_NAME "exec"
#define ID_ATTR_NAME "id"
#define NAME_ATTR_NAME "name"
#define DEFAULT_ATTR_NAME "default"
#define PATH_TAG_NAME "path"
#define PROFILE_TAG_NAME "profile"
#define ROOT_TAG_NAME "configurations"

using namespace std;

Configuration::Configuration(const QString& filePath)
    : m_filePath(filePath) {
    //m_profiles.append(new Profile);
}

Configuration::~Configuration() {
    qDeleteAll(m_profiles);
}

bool Configuration::load() {
    QFile f(m_filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        cerr << "Unable to open '" << m_filePath.toStdString() << "'" << endl;
        return false;
    }
    QDomDocument doc;
    if (!doc.setContent(&f)) {
        cerr << "Unable to load '" << m_filePath.toStdString() << "'" << endl;
        f.close();
        return false;
    }

    QDomElement e = doc.documentElement();
    if (e.tagName() == ROOT_TAG_NAME) {
        QDomElement pe = e.firstChildElement(PROFILE_TAG_NAME);
        while (!pe.isNull()) {
            bool ok = false;
            bool ok2 = false;
            unsigned id = pe.attribute(ID_ATTR_NAME).toUInt(&ok);
            unsigned isDefault = pe.attribute(DEFAULT_ATTR_NAME).toUInt(&ok2);
            if (ok and ok2) {
                QString name = pe.attribute(NAME_ATTR_NAME);
                QDomNode n = pe.firstChild();
                Profile* p = new Profile(id, name);
                p->setDefault(isDefault);
                while (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement ae = n.toElement();
                        if (ae.tagName() == EXEC_TAG_NAME) {
                            p->setGPGExecutable(ae.text());
                        } else if (ae.tagName() == PATH_TAG_NAME) {
                            p->setConfigurationPath(ae.text());
                        }
                    }
                    n = n.nextSibling();
                }
                m_profiles.append(p);
            }
            pe = pe.nextSiblingElement(PROFILE_TAG_NAME);
        }
    }
    f.close();
    return true;
}

Profile* Configuration::getProfileById(unsigned id) const {
    for (Profile* p : m_profiles) {
        if (p->getId() == id) {
            return p;
        }
    }
    return nullptr;
}

Profile* Configuration::getDefaultProfile() const {
    for (Profile* p : m_profiles) {
        if (p->isDefault()) {
            return p;
        }
    }
    return nullptr;
}

const QList<Profile*>& Configuration::getProfiles() const {
    return m_profiles;
}

void Configuration::addProfile(Profile* p) {
    m_profiles.append(p);
}

bool Configuration::save() {
    QDomDocument doc;
    QDomElement root = doc.createElement(ROOT_TAG_NAME);
    doc.appendChild(root);
    for (int i = 0; i < m_profiles.size(); ++i) {
        Profile* p = m_profiles.at(i);
        QDomElement pe = doc.createElement(PROFILE_TAG_NAME);
        pe.setAttribute(ID_ATTR_NAME, p->getId());
        pe.setAttribute(NAME_ATTR_NAME, p->getName());
        pe.setAttribute(DEFAULT_ATTR_NAME, p->isDefault());
        addNode(EXEC_TAG_NAME, p->getGPGExecutable(), doc, pe);
        addNode(PATH_TAG_NAME, p->getConfigurationPath(), doc, pe);
        root.appendChild(pe);
    }

    QFile f(m_filePath);
    if (!f.open(QIODevice::WriteOnly)) {
        return false;
    }
    QTextStream out(&f);
    out << doc.toString();
    f.close();
    return true;
}

void Configuration::addNode(const QString& name, const QString& value,
                            QDomDocument& doc, QDomElement& parent) {
    QDomElement e = doc.createElement(name);
    e.appendChild(doc.createTextNode(value));
    parent.appendChild(e);
}
