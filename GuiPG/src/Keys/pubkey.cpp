#include "pubkey.h"

PubKey::PubKey(const KeyScope keyScope,
               const Validity validity,
               const unsigned length,
               const Algorithm algo,
               const QString keyId,
               const QDate creationDate,
               const QDate expirationDate,
               const QString capabilities,
               QString fpr
               ) : SubSecKey(keyScope, length, algo, keyId, creationDate),
                   m_validity(validity),
                   m_expirationDate(expirationDate),
                   m_capabilities(capabilities)
{
    m_fpr = fpr;
}

PubKey::~PubKey()
{

}

GpgObject::Validity PubKey::getValidity() const {
    return m_validity;
}

QDate PubKey::getExpirationDate() const {
    return m_expirationDate;
}

QString PubKey::getCapabilities() const {
    return m_capabilities;
}
