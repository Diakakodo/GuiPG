#include "key.h"

QString Key::keyScopeToStr(KeyScope ks) {

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
    qDeleteAll(m_sigs); // à virer car destructeur virtuel pure
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
