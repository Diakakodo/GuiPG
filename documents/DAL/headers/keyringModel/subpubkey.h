#ifndef SUBPUBKEY_H
#define SUBPUBKEY_H

#include "pubkey.h"
#include "signature.h"

class SubPubKey : public PubKey {
    Q_OBJECT

    public:
        SubPubKey(const QString keyScope,
                  const QString validity,
                  const unsigned length,
                  const QString algo,
                  const QString keyId,
                  const QDate creationDate,
                  const QDate expirationDate,
                  const QString capabilities,
                  QString fpr = "");
        ~SubPubKey();

        const QList<Signature*> getSignatures() const;

        void addSignature(Signature* sig);


    private:
        QList<Signature*> m_sigs;
};

#endif // SUBPUBKEY_H
