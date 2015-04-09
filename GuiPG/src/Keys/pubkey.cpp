#include "pubkey.h"

QString PubKey::trustToStr(Trust t) {
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

PubKey::PubKey()
{

}

PubKey::~PubKey()
{

}

PubKey::Trust PubKey::getTrust() const {
    return m_trust;
}

const QList<SubKey*> PubKey::getSubKeys() const {
    return m_subKeys;
}

void PubKey::addSubKey(SubKey* sub) {
    m_subKeys.append(sub);
}

