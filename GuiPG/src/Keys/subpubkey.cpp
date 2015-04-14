#include "subpubkey.h"

SubPubKey::SubPubKey(const KeyScope keyScope,
                     const Validity validity,
                     const unsigned length,
                     const Algorithm algo,
                     const QString keyId,
                     const QDate creationDate,
                     const QDate expirationDate,
                     const QString capabilities,
                     QString fpr) : SubSecKey(keyScope,
                                              length,
                                              algo,
                                              keyId,
                                              creationDate,
                                              fpr)
{
    m_validity = validity;
    m_expirationDate = expirationDate;
    m_capabilities = capabilities;

}

SubPubKey::~SubPubKey()
{

}

const QList<Signature*> SubPubKey::getSignatures() const {
    return m_sigs;
}

void SubPubKey::addSignature(Signature *sig) {
    m_sigs.append(sig);
}

