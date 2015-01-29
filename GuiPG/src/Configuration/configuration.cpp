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
#define ID_ATTR_NAME "id"
#define NAME_ATTR_NAME "name"
#define PATH_TAG_NAME "path"
#define PROFILE_TAG_NAME "profile"
#define ROOT_TAG_NAME "configurations"

using namespace std;

Configuration::Configuration(const QString& filePath)
    : m_filePath(filePath) {
    m_profiles.append(new Profile());
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
            unsigned id = pe.attribute(ID_ATTR_NAME).toUInt(&ok);
            if (ok) {
                QString name = pe.attribute(NAME_ATTR_NAME);
                QDomNode n = pe.firstChild();
                Profile* p = new Profile(id, name);
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

const QList<Profile*>& Configuration::getProfiles() const {
    return m_profiles;
}

//TODO
bool Configuration::save() {
    return false;
}
