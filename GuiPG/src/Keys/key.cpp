#include "key.h"

//Key::Key(Scope s,
//         Algorithm a,
//         unsigned length,
//         Validity v,
//         const QString& id,
//         const QDate &creation,
//         const QDate &expiration,
//         const QString& owner,
//         Validity trust)
//        : Signature(a, id, creation, owner),
//          m_length(length),
//          m_val(v),
//          m_scope(s),
//          m_expiration(expiration),
//          m_trust(trust) {
//
//}

Key::Key(const KeyScope keyScope,
        const Validity validity,
        const unsigned length,
        const Algorithm algo,
        const QString keyId,
        const QDate creationDate,
        const QDate expirationDate,
        const QString capabilities,
        QString fpr
        ) : GpgObject(creationDate, fpr),
            m_keyScope(keyScope),
            m_validity(validity),
            m_length(length),
            m_algo(algo),
            m_keyId(keyId),
            m_expirationDate(expirationDate),
            m_capabilities(capabilities)
{}

Key::~Key() {
    //qDeleteAll(m_sigs);
}

unsigned Key::getLength() const {
    return m_length;
}

Key::Validity Key::getValidity() const {
    return m_validity;
}

Key::KeyScope Key::getKeyScope() const {
    return m_keyScope;
}

QDate Key::getExpirationDate() const {
    return m_expirationDate;
}
