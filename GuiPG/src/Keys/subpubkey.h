#ifndef SUBPUBKEY_H
#define SUBPUBKEY_H

#include "subseckey.h"
#include "signature.h"

class SubPubKey : public SubSecKey {
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

        QString getValidity();
        QDate getExpirationDate();
        QString getCapabilities();

    private:
        QList<Signature*> m_sigs;
        QString m_validity;
        QDate m_expirationDate;
        QString m_capabilities;
};

#endif // SUBPUBKEY_H
