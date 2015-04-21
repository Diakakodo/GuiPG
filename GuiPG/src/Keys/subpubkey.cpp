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

void SubPubKey::setSubSecKey(SubSecKey* ssb) {
    m_ssb = ssb;
}

SubSecKey* SubPubKey::getSubSecKey() const {
    return m_ssb;
}

bool SubPubKey::hasSubSecKey() {
    return m_ssb != nullptr;
}

