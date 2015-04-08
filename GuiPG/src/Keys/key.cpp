#include "key.h"

QString Key::validityToStr(Validity v) {
    switch (v) {
        case VAL_UNKNOWN:
            return "Inconnue";
        case VAL_MISSING_SSIG:
            return "Invalide (signature manquante)";
        case VAL_DISABLE:
            return "Désactivée";
        case VAL_REVOKED:
            return "Révoquée";
        case VAL_EXPIRED:
            return "Expirée";
        case VAL_NO_VALUE:
            return "Inconnue";
        case VAL_UNDEFINED:
            return "Non définie";
        case VAL_VALID:
            return "Valide"
        case VAL_MARGINAL:
            return "Marginale",
        case VAL_FULLY:
            return "Complète";
        case VAL_ULTIMATELY:
            return "Ultime";
    }
    return "";
}

QString Key::trustToStr(Trust t) {
    switch (t) {
        case VAL_UNKNOWN:
            return "Inconnue";
        case VAL_MISSING_SSIG:
            return "Invalide (signature manquante)";
        case VAL_DISABLE:
            return "Désactivée";
        case VAL_REVOKED:
            return "Révoquée";
        case VAL_EXPIRED:
            return "Expirée";
        case VAL_NO_VALUE:
            return "Inconnue";
        case VAL_UNDEFINED:
            return "Ne sais pas";
        case VAL_VALID:
            return "Pas confiance"
        case VAL_MARGINAL:
            return "Légère",
        case VAL_FULLY:
            return "Complète";
        case VAL_ULTIMATELY:
            return "Ultime";
    }
    return "";
}

Key::Key(Scope s,
         Algorithm a,
         unsigned length,
         Validity v,
         const QString& id,
         const QDate &creation,
         const QDate &expiration,
         const QString& owner,
         Validity trust)
        : Signature(a, id, creation, owner),
          m_length(length),
          m_val(v),
          m_scope(s),
          m_expiration(expiration),
          m_trust(trust) {

}

Key::~Key() {
    qDeleteAll(m_sigs);
}

const QList<Key*> Key::getSubKeys() const {
    return m_subkeys;
}

unsigned Key::getLength() const {
    return m_length;
}

Key::Validity Key::getValidity() const {
    return m_val;
}

Key::Scope Key::getScope() const {
    return m_scope;
}

const QDate& Key::getExpirationDate() const {
    return m_expiration;
}

void Key::addSubKey(Key *k) {
    m_subkeys.append(k);
}

void Key::removeSubKey(Key *k) {
    m_subkeys.removeAll(k);
}

void Key::setExpirationDate(const QDate &dt) {
    m_expiration = dt;
}

void Key::addSignature(Signature *s) {
    m_sigs.append(s);
}

const QList<Signature*>& Key::getSignatures() const {
    return m_sigs;
}

Key::Validity Key::getTrust() const {
    return m_trust;
}
