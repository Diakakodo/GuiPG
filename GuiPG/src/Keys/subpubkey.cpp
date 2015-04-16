#include "subpubkey.h"

SubPubKey::SubPubKey(const QString keyScope,
                     const QString validity,
                     const unsigned length,
                     const QString algo,
                     const QString keyId,
                     const QDate creationDate,
                     const QDate expirationDate,
                     const QString capabilities,
                     QString fpr) : PubKey(keyScope,
                                           validity,
                                           length,
                                           algo,
                                           keyId,
                                           creationDate,
                                           expirationDate,
                                           capabilities,
                                           fpr)
{

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
