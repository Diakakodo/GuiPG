#include "pubkey.h"
#include <QDebug>
PubKey::PubKey(const QString keyScope,
               QString validity,
               const unsigned length,
               const QString algo,
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
    qDeleteAll(m_sigs);
}

QString PubKey::getValidity() const {
    return m_validity;
}

QDate PubKey::getExpirationDate() const {
    return m_expirationDate;
}

QString PubKey::getCapabilities() const {
    return m_capabilities;
}

const QList<Signature*> PubKey::getSignatures() const {
    return m_sigs;
}

void PubKey::addSignature(Signature *sig) {
    m_sigs.append(sig);
}
