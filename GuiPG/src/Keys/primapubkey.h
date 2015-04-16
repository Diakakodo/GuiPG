#ifndef PRIMAPUBKEY_H
#define PRIMAPUBKEY_H

#include "pubkey.h"
#include "subpubkey.h"
#include "uid.h"

#define TRUST_UNKNOWN         "o"
#define TRUST_MISSING_SSIG    "i"
#define TRUST_DISABLE         "d"
#define TRUST_REVOKED         "r"
#define TRUST_EXPIRED         "e"
#define TRUST_NO_VALUE        "-"
#define TRUST_UNDEFINED       "q"
#define TRUST_INVALID         "n"
#define TRUST_MARGINAL        "m"
#define TRUST_FULLY           "f"
#define TRUST_ULTIMATELY      "u"
#define TRUST_PRIVATE_PART    "w"
#define TRUST_SPECIAL         "s"

class PrimaPubKey : public PubKey {
    Q_OBJECT

    public:

        static QString trustToStr(QString t);

        PrimaPubKey (const QString keyScope,
               QString validity,
               const unsigned length,
               const QString algo,
               const QString keyId,
               const QDate creationDate,
               const QDate expirationDate,
               const QString trust,
               const QString capabilities,
               QString fpr = "");
        ~PrimaPubKey();

        QString getTrust() const;
        const QList<SubPubKey*> getSubPubKeyList() const;
        const QList<Uid*> getUidList() const;

        void addSubPubKey(SubPubKey* subPubKey);
        void addUid(Uid* uid);
        Uid* getPrimaryUid();
        void setPrimaryUid(Uid* uid);

    private:
        QString m_trust;
        QList<SubPubKey*> m_subPubKeyList;
        QList<Uid*> m_uidList;
        Uid* m_primaryUid;
};

#endif // PRIMAPUBKEY_H
