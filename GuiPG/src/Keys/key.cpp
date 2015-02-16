#include "key.h"

QString Key::validityToStr(Validity v) {
    switch (v) {
        case VAL_EXPIRED:
            return "Expirée";
        case VAL_FULLY:
            return "Totalement valide";
        case VAL_INVALID:
            return "Invalide";
        case VAL_MARGINAL:
            return "Valide";
        case VAL_MISSING_SSIG:
            return "Singnature manquante";
        case VAL_NO_VALUE:
            return "";
        case VAL_PRIVATE_PART:
            return "";
        case VAL_REVOKED:
            return "Révoquée";
        case VAL_SPECIAL:
            return "Spéciale";
        case VAL_ULTIMATELY:
            return "Ultime";
        case VAL_UNDEFINED:
            return "Indéfinie";
        case VAL_UNKNOWN:
            return "Inconnue";
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
         const QString& owner)
        : m_length(length),
          m_val(v),
          m_scope(s),
          m_algo(a),
          m_id(id),
          m_creation(creation),
          m_expiration(expiration),
          m_owner(owner) {

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

Key::Algorithm Key::getAlgorithm() const {
    return m_algo;
}

const QString& Key::getId() const {
    return m_id;
}

const QDate& Key::getCreationDate() const {
    return m_creation;
}

const QDate& Key::getExpirationDate() const {
    return m_expiration;
}

const QString& Key::getOwner() const {
    return m_owner;
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
