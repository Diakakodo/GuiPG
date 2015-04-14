#include "subseckey.h"

SubSecKey::SubSecKey(const QString keyScope,
                const unsigned length,
                const QString algo,
                const QString keyId,
                const QDate creationDate,
                QString fpr
                ) : GpgObject(creationDate, fpr),
                    m_keyScope(keyScope),
                    m_length(length),
                    m_algo(algo),
                    m_keyId(keyId)
{}

SubSecKey::~SubSecKey() {
    //qDeleteAll(m_sigs);
}

QString SubSecKey::getKeyScope() const {
    return m_keyScope;
}

unsigned SubSecKey::getLength() const {
    return m_length;
}

QString SubSecKey::getAlgo() const {
    return m_algo;
}

QString SubSecKey::getKeyId() const {
    return m_keyId;
}

QString SubSecKey::getValidity() {
    return VALIDITY_EMPTY;
}
