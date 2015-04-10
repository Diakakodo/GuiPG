#ifndef PUBKEY_H
#define PUBKEY_H

#include "subseckey.h"

class PubKey : public SubSecKey {
    Q_OBJECT

    public:

        enum Capabilitie {
            CAP_PRIM_ENCRYPT            = 'E',
            CAP_PRIM_SIGN               = 'S',
            CAP_PRIM_CERTIFY            = 'C',
            CAP_PRIM_AUTHENTIFICATION   = 'A',
            CAP_PRIM_DISABLE            = 'D',
            CAP_ENCRYPT                 = 'e',
            CAP_SIGN                    = 's',
            CAP_CERTIFY                 = 'c',
            CAP_AUTHENTIFICATION        = 'a',
            CAP_UNKNOWN                 = '?',
            CAP_NONE                    = 256
        };

        PubKey(const KeyScope keyScope,
               const Validity validity,
               const unsigned length,
               const Algorithm algo,
               const QString keyId,
               const QDate creationDate,
               const QDate expirationDate,
               const QString capabilities,
               QString fpr = ""
               );
        vitural ~PubKey() = 0;

        Validity getValidity() const;
        QDate getExpirationDate() const;
        QString getCapabilities() const;

    private:
        Validity m_validity;
        QDate m_expirationDate;
        QString m_capabilities;

};

#endif // PUBKEY_H
