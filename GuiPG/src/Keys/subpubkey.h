#ifndef SUBPUBKEY_H
#define SUBPUBKEY_H

#include "subseckey.h"
#include "signature.h"

class SubPubKey : public Key {
    Q_OBJECT

    public:
        SubPubKey();
        ~SubPubKey();

        const QList<Signature*> getSignatures() const;
        void addSignature(Signature* sig);

    private:
        QList<Signature*> m_sigs;
};

#endif // SUBPUBKEY_H
