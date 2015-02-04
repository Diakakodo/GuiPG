#include "key.h"

Key::Key(Scope s,
         Algorithm a,
         unsigned length,
         Validity v,
         const QString& id,
         const QDateTime& creation,
         const QDateTime& expiration,
         const QString& owner,
         const QString& comment,
         const QString& email,
         unsigned uid)
        : m_length(length),
          m_val(v),
          m_scope(s),
          m_algo(a),
          m_id(id),
          m_creation(creation),
          m_expiration(expiration),
          m_owner(owner),
          m_comment(comment),
          m_email(email),
          m_uid(uid) {

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

const QDateTime& Key::getCreationDate() const {
    return m_creation;
}

const QDateTime& Key::getExpirationDate() const {
    return m_expiration;
}

const QString& Key::getOwner() const {
    return m_owner;
}

const QString& Key::getComment() const {
    return m_comment;
}

const QString& Key::getEmail() const {
    return m_email;
}

unsigned Key::getUserId() const {
    return m_uid;
}

void Key::addSubKey(Key *k) {
    m_subkeys.append(k);
}

void Key::removeSubKey(Key *k) {
    m_subkeys.removeAll(k);
}

void Key::setExpirationDate(const QDateTime &dt) {
    m_expiration = dt;
}
