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
    m_exec(DEFAULT_EXEC), m_path(DEFAULT_PATH), m_signColor(0, 0, 255) {

    m_validityColors.insert(GpgObject::VAL_UNKNOWN     , QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_MISSING_SSIG, QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_DISABLE     , QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_REVOKED     , QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_EXPIRED     , QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_NO_VALUE    , QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_UNDEFINED   , QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_INVALID     , QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_MARGINAL    , QColor(255, 165,   0));
    m_validityColors.insert(GpgObject::VAL_FULLY       , QColor(  0, 255,   0));
    m_validityColors.insert(GpgObject::VAL_ULTIMATELY  , QColor(  0, 255,   0));
    m_validityColors.insert(GpgObject::VAL_PRIVATE_PART, QColor(255,   0,   0));
    m_validityColors.insert(GpgObject::VAL_SPECIAL     , QColor(255,   0,   0));


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

void Profile::setGPGExecutable(const QString& exec) {
    m_exec = exec;
}

const QString& Profile::getConfigurationPath() const {
    return m_path;
}

void Profile::setConfigurationPath(const QString& path) {
    m_path = path;
}

QColor Profile::getValidityColor(GpgObject::Validity v) const {
    return m_validityColors.value(v);
}

void Profile::setValidityColor(GpgObject::Validity v, const QColor &c) {
    m_validityColors.insert(v, c);
}

const QHash<GpgObject::Validity, QColor>& Profile::getValidityColors() const {
    return m_validityColors;
}

const QColor& Profile::getSignatureColor() const {
    return m_signColor;
}

void Profile::setSignatureColor(const QColor &c) {
    m_signColor = c;
}
