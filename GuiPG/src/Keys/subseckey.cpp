#include "subseckey.h"

SubSecKey::SubSecKey(const KeyScope keyScope,
                const unsigned length,
                const Algorithm algo,
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

SubSecKey::KeyScope SubSecKey::getKeyScope() const {
    return m_keyScope;
}

unsigned SubSecKey::getLength() const {
    return m_length;
}

GpgObject::Algorithm SubSecKey::getAlgo() const {
    return m_algo;
}

QString SubSecKey::getKeyId() const {
    return m_keyId;
}

GpgObject::Validity SubSecKey::getValidity() {
    return Validity::VAL_NO_VALUE;
}
