#include "subkey.h"

SubKey::SubKey()
{

}

SubKey::~SubKey()
{

}

const QList<Signature*>& SubKey::getSignatures() const {
    return m_sigs;
}

void SubKey::addSignature(Signature *s) {
    m_sigs.append(s);
}

