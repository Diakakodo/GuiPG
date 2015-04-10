#include "primapubkey.h"

QString PrimaPubKey::trustToStr(Trust t) {
    switch (t) {
        case TRUST_UNKNOWN:
            return "Inconnue";
        case TRUST_MISSING_SSIG:
            return "Invalide (signature manquante)";
        case TRUST_DISABLE:
            return "Désactivée";
        case TRUST_REVOKED:
            return "Révoquée";
        case TRUST_EXPIRED:
            return "Expirée";
        case TRUST_NO_VALUE:
            return "Pas de valeur";
        case TRUST_UNDEFINED:
            return "Sans avis";
        case TRUST_INVALID:
            return "Aucune";
        case TRUST_MARGINAL:
            return "Légère";
        case TRUST_FULLY:
            return "Complète";
        case TRUST_ULTIMATELY:
            return "Ultime";
    }
    return "";
}

PrimaPubKey::PrimaPubKey(const KeyScope keyScope,
                         const Validity validity,
                         const unsigned length,
                         const Algorithm algo,
                         const QString keyId,
                         const QDate creationDate,
                         const QDate expirationDate,
                         const Trust trust,
                         const QString capabilities,
                         QString fpr) : PubKey(keyScope,
                                               validity,
                                               length,
                                               algo,
                                               keyId,
                                               creationDate,
                                               expirationDate,
                                               capabilities),
                            m_trust(trust)

{}

PrimaPubKey::~PrimaPubKey()
{

}

PrimaPubKey::Trust PrimaPubKey::getTrust() const {
    return m_trust;
}

const QList<SubKey*> PrimaPubKey::getSubKeys() const {
    return m_subKeys;
}

void PrimaPubKey::addSubKey(SubKey* sub) {
    m_subKeys.append(sub);
}

