#ifndef PRIMAPUBKEY_H
#define PRIMAPUBKEY_H

#include "pubkey.h"
#include "subpubkey.h"
#include "uid.h"

class PrimaPubKey : public PubKey {
    Q_OBJECT

    public:

        enum Trust {
            TRUST_UNKNOWN         = 'o',
            TRUST_MISSING_SSIG    = 'i',
            TRUST_DISABLE         = 'd',
            TRUST_REVOKED         = 'r',
            TRUST_EXPIRED         = 'e',
            TRUST_NO_VALUE        = '-',
            TRUST_UNDEFINED       = 'q',
            TRUST_INVALID         = 'n',
            TRUST_MARGINAL        = 'm',
            TRUST_FULLY           = 'f',
            TRUST_ULTIMATELY      = 'u',
            TRUST_PRIVATE_PART    = 'w',
            TRUST_SPECIAL         = 's'
        };

        static QString trustToStr(Trust t);

        PrimaPubKey (const KeyScope keyScope,
               const Validity validity,
               const unsigned length,
               const Algorithm algo,
               const QString keyId,
               const QDate creationDate,
               const QDate expirationDate,
               const Trust trust,
               const QString capabilities,
               QString fpr = "");
        ~PrimaPubKey();

        Trust getTrust() const;
        const QList<SubPubKey*> getSubPubKeyList() const;
        const QList<Uid*> getUidList() const;

        void addSubPubKey(SubPubKey* subPubKey);
        void addUid(Uid* uid);

    private:
        Trust m_trust;
        QList<SubPubKey*> m_subPubKeyList;
        QList<Uid*> m_uidList;
};

#endif // PRIMAPUBKEY_H
