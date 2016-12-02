#include "primaseckey.h"

PrimaSecKey::PrimaSecKey(const QString keyScope,
                         const unsigned length,
                         const QString algo,
                         const QString keyId,
                         const QDate creationDate,
                         const QDate expirationDate,
                         QString fpr
                         ) : SubSecKey(keyScope,
                                       length,
                                       algo,
                                       keyId,
                                       creationDate,
                                       fpr)
{
    m_expirationDate = expirationDate;
}

PrimaSecKey::~PrimaSecKey()
{
    qDeleteAll(m_uids);
}


void PrimaSecKey::setPrimaryPubKey(PrimaPubKey* pub) {
    m_pub = pub;
}

PrimaPubKey* PrimaSecKey::getPrimaryPubKey() {
    return m_pub;
}

bool PrimaSecKey::hasPrimaSecKey() {
    return m_pub != nullptr;
}


QDate PrimaSecKey::getExpirationDate() const {
    return m_expirationDate;
}

QList<Uid*> PrimaSecKey::getUidList() const {
    return m_uids;
}

const QList<SubSecKey*> PrimaSecKey::getSubSecKeyList() const {
    return m_subSecKeyList;
}

void PrimaSecKey::addUid(Uid* uid) {
    m_uids.append(uid);
}

void PrimaSecKey::addSubSecKey(SubSecKey* subSecKey) {
    m_subSecKeyList.append(subSecKey);
}
