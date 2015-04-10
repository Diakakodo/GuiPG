#include "subpubkey.h"

SubPubKey::SubPubKey()
{

}

SubPubKey::~SubPubKey()
{

}

const QList<Signature*>& SubPubKey::getSignatures() const {
    return m_sigs;
}

void SubPubKey::addSignature(Signature *s) {
    m_sigs.append(s);
}

