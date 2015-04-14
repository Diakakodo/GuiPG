#ifndef SUBPUBKEY_H
#define SUBPUBKEY_H

#include "subseckey.h"
#include "signature.h"

class SubPubKey : public SubSecKey {
    Q_OBJECT

    public:
        SubPubKey(const KeyScope keyScope,
                  const Validity validity,
                  const unsigned length,
                  const Algorithm algo,
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
