#include "configuration.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <iostream>

#define EXEC_TAG_NAME "exec"
#define ID_ATTR_NAME "id"
#define NAME_ATTR_NAME "name"
#define DEFAULT_PROFILE_ATTR_NAME "defaultProfileId"
#define PATH_TAG_NAME "path"
#define PROFILES_TAG_NAME "profiles"
#define PROFILE_TAG_NAME "profile"
#define ROOT_TAG_NAME "configurations"
#define VALIDITY_COLOR_TAG_NAME "validity_color"
#define BLUE_ATTRIBUTE "blue"
#define GREEN_ATTRIBUTE "green"
#define RED_ATTRIBUTE "red"
#define VALUE_ATTRIBUTE "value"
#define SIG_COLOR_TAG_NAME "sig_color"

using namespace std;

Configuration::Configuration(const QString& filePath)
    : m_filePath(filePath) {
}

Configuration::~Configuration() {
    qDeleteAll(m_profiles);
}

bool Configuration::load() {
    QFile f(m_filePath);
    if (!f.exists()) {
        return true;
    }
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
        QDomElement profiles = e.firstChildElement(PROFILES_TAG_NAME);
        QDomElement pe = profiles.firstChildElement(PROFILE_TAG_NAME);
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
                        } else if (ae.tagName() == VALIDITY_COLOR_TAG_NAME) {
                            QColor c(
                                        ae.attribute(RED_ATTRIBUTE).toInt(),
                                        ae.attribute(GREEN_ATTRIBUTE).toInt(),
                                        ae.attribute(BLUE_ATTRIBUTE).toInt()
                            );
                            p->setValidityColor((Key::Validity) ae.attribute(VALUE_ATTRIBUTE).toInt(), c);
                        } else if (ae.tagName() == SIG_COLOR_TAG_NAME) {
                            QColor c(
                                        ae.attribute(RED_ATTRIBUTE).toInt(),
                                        ae.attribute(GREEN_ATTRIBUTE).toInt(),
                                        ae.attribute(BLUE_ATTRIBUTE).toInt()
                            );
                            p->setSignatureColor(c);
                        }
                    }
                    n = n.nextSibling();
                }
                m_profiles.append(p);
            }
            pe = pe.nextSiblingElement(PROFILE_TAG_NAME);
        }
        bool ok = false;
        unsigned defaultProfileId = profiles.attribute(DEFAULT_PROFILE_ATTR_NAME).toUInt(&ok);
        if (ok) {
            setDefaultProfileId(defaultProfileId);
        }
    }
    f.close();
    return true;
}

bool Configuration::save() {
    QDomDocument doc;
    QDomElement root = doc.createElement(ROOT_TAG_NAME);
    doc.appendChild(root);
    QDomElement profiles = doc.createElement(PROFILES_TAG_NAME);
    root.appendChild(profiles);
    profiles.setAttribute(DEFAULT_PROFILE_ATTR_NAME, m_defaultProfileId);
    for (int i = 0; i < m_profiles.size(); ++i) {
        Profile* p = m_profiles.at(i);
        QDomElement pe = doc.createElement(PROFILE_TAG_NAME);
        pe.setAttribute(ID_ATTR_NAME, p->getId());
        pe.setAttribute(NAME_ATTR_NAME, p->getName());
        addNode(EXEC_TAG_NAME, p->getGPGExecutable(), doc, pe);
        addNode(PATH_TAG_NAME, p->getConfigurationPath(), doc, pe);
        const QHash<Key::Validity, QColor> validityColors = p->getValidityColors();
        for (Key::Validity v : validityColors.keys()) {
            QDomElement e = createColorElement(VALIDITY_COLOR_TAG_NAME, validityColors.value(v), doc);
            e.setAttribute(VALUE_ATTRIBUTE, (int) v);
            pe.appendChild(e);
        }
        pe.appendChild(createColorElement(SIG_COLOR_TAG_NAME, p->getSignatureColor(), doc));
        profiles.appendChild(pe);
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

Profile* Configuration::getDefaultProfile() const {
    for (Profile* p : m_profiles) {
        if (p->getId() == m_defaultProfileId) {
            return p;
        }
    }
    return nullptr;
}

unsigned Configuration::getDefaultProfileId() const {
    return m_defaultProfileId;
}

Profile* Configuration::getProfileById(unsigned id) const {
    for (Profile* p : m_profiles) {
        if (p->getId() == id) {
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

void Configuration::deleteProfile(unsigned profileId) {
    m_profiles.removeOne(getProfileById(profileId));
    save();
}

void Configuration::setDefaultProfileId(unsigned profileId) {
    for (Profile* p : m_profiles) {
        if (p->getId() == profileId) {
            m_defaultProfileId = profileId;
            return;
        }
    }
    m_defaultProfileId = 0;
}

void Configuration::addNode(const QString& name, const QString& value,
                            QDomDocument& doc, QDomElement& parent) {
    QDomElement e = doc.createElement(name);
    e.appendChild(doc.createTextNode(value));
    parent.appendChild(e);
}

QDomElement Configuration::createColorElement(const QString& tag, const QColor& color, QDomDocument& doc) {
    QDomElement e = doc.createElement(tag);
    e.setAttribute(RED_ATTRIBUTE, color.red());
    e.setAttribute(BLUE_ATTRIBUTE, color.blue());
    e.setAttribute(GREEN_ATTRIBUTE, color.green());
    return e;
}
