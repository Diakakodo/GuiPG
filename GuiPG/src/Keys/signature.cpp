#include "signature.h"

Signature::Signature(Algorithm a,
                     const QString &id,
                     const QDate &creation,
                     const QString &owner)
                    : m_algo(a),
                      m_id(id),
                      m_creation(creation),
                      m_owner(owner) {
}

const QString& Signature::getOwner() const {
    return m_owner;
}

Signature::Algorithm Signature::getAlgorithm() const {
    return m_algo;
}

const QDate& Signature::getCreationDate() const {
    return m_creation;
}

const QString& Signature::getId() const {
    return m_id;
}
