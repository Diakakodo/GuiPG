#ifndef PUBLICKEY_H
#define PUBLICKEY_H

#include "key.h"
#include "subkey.h"
#include "uid.h"

class PubKey : public Key {
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

        PubKey(const KeyScope keyScope,
               const Validity validity,
               const unsigned length,
               const Algorithm algo,
               const QString keyId,
               const QDate creationDate,
               const QDate expirationDate,
               const Trust trust,
               const QString capabilities,
               QString fpr = "");
        ~PubKey();

        Trust getTrust() const;
        const QList<SubKey*> getSubKeys() const;
        const QList<Uid*> getUids() const;

        void addSubKey(SubKey* sub);
        void addUid(Uid* uid);

    private:
        Trust m_trust;
        QList<SubKey*> m_subKeys;
        QList<Uid*> m_uids;
};

#endif // PUBLICKEY_H
