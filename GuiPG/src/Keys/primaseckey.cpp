#include "primaseckey.h"

PrimaSecKey::PrimaSecKey(const KeyScope keyScope,
                         const unsigned length,
                         const Algorithm algo,
                         const QString keyId,
                         const QDate creationDate,
                         const QDate expirationDate,
                         QString fpr
                         ) : SubSecKey(keyScope,
                                       length,
                                       algo,
                                       keyId,
                                       creationDate,
                                       fpr),
                             m_expirationDate(expirationDate)
   {}

PrimaSecKey::~PrimaSecKey()
{

}

QDate PrimaSecKey::getExpirationDate() const {
    return m_expirationDate;
}

Uid PrimaSecKey::getUid() const {
    return m_uid;
}

const QList<SubSecKey*> PrimaSecKey::getSubSecKeyList() const {
    return m_subSecKeyList;
}

void PrimaSecKey::setUid(Uid uid) {
    m_uid = uid;
}

void PrimaSecKey::addSubSecKey(SubSecKey* subSecKey) {
    m_subSecKeyList.append(subSecKey);
}
