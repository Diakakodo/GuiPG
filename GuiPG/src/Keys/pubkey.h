#ifndef PUBKEY_H
#define PUBKEY_H

#include "subseckey.h"
#include "signature.h"

#define CAP_PRIM_ENCRYPT            'E'
#define CAP_PRIM_SIGN               'S'
#define CAP_PRIM_CERTIFY            'C'
#define CAP_PRIM_AUTHENTIFICATION   'A'
#define CAP_PRIM_DISABLE            'D'
#define CAP_ENCRYPT                 'e'
#define CAP_SIGN                    's'
#define CAP_CERTIFY                 'c'
#define CAP_AUTHENTIFICATION        'a'
#define CAP_UNKNOWN                 '?'
#define CAP_NONE                    ''

class PubKey : public SubSecKey {
    Q_OBJECT

    public:

        PubKey(const QString keyScope,
               QString validity,
               const unsigned length,
               const QString algo,
               const QString keyId,
               const QDate creationDate,
               const QDate expirationDate,
               const QString capabilities,
               QString fpr = ""
               );
        virtual ~PubKey() = 0;

        QString getValidity() const;
        QDate getExpirationDate() const;
        QString getCapabilities() const;
        const QList<Signature*> getSignatures() const;

        void addSignature(Signature* sig);

    protected:
        QString m_validity;
        QDate m_expirationDate;
        QString m_capabilities;
        QList<Signature*> m_sigs;

};

#endif // PUBKEY_H
