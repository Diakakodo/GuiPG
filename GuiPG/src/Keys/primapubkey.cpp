#include "primapubkey.h"

QString PrimaPubKey::trustToStr(QString t) {
    if (t == TRUST_UNKNOWN)
        return "Inconnue";
    if (t == TRUST_MISSING_SSIG)
        return "Invalide (signature manquante)";
    if (t == TRUST_DISABLE)
        return "Désactivée";
    if (t == TRUST_REVOKED)
        return "Révoquée";
    if (t == TRUST_EXPIRED)
        return "Expirée";
    if (t == TRUST_NO_VALUE)
        return "Pas de valeur";
    if (t == TRUST_UNDEFINED)
        return "Sans avis";
    if (t == TRUST_INVALID)
        return "Aucune";
    if (t == TRUST_MARGINAL)
        return "Légère";
    if (t == TRUST_FULLY)
        return "Complète";
    if (t == TRUST_ULTIMATELY)
        return "Ultime";
    return "";
}

PrimaPubKey::PrimaPubKey(const QString keyScope,
                         QString validity,
                         const unsigned length,
                         const QString algo,
                         const QString keyId,
                         const QDate creationDate,
                         const QDate expirationDate,
                         const QString trust,
                         const QString capabilities,
                         QString fpr) : PubKey(keyScope,
                                               validity,
                                               length,
                                               algo,
                                               keyId,
                                               creationDate,
                                               expirationDate,
                                               capabilities,
                                               fpr),
                            m_trust(trust)

{}

PrimaPubKey::~PrimaPubKey()
{

}

QString PrimaPubKey::getTrust() const {
    return m_trust;
}

const QList<SubPubKey*> PrimaPubKey::getSubPubKeyList() const {
    return m_subPubKeyList;
}

const QList<Uid*> PrimaPubKey::getUidList() const {
    return m_uidList;
}

void PrimaPubKey::addSubPubKey(SubPubKey* subPubKey) {
    m_subPubKeyList.append(subPubKey);
}

void PrimaPubKey::addUid(Uid* uid) {
    m_uidList.append(uid);
}

