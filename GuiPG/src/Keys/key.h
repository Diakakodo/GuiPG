#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QList>
#include <QDate>
#include "gpgobject.h"

class Key : public GpgObject {
    Q_OBJECT

    public:
        enum Validity {
            VAL_UNKNOWN         = 'o',
            VAL_MISSING_SSIG    = 'i',
            VAL_DISABLE         = 'd',
            VAL_REVOKED         = 'r',
            VAL_EXPIRED         = 'e',
            VAL_NO_VALUE        = '-',
            VAL_UNDEFINED       = 'q',
            VAL_VALID           = 'n',
            VAL_MARGINAL        = 'm',
            VAL_FULLY           = 'f',
            VAL_ULTIMATELY      = 'u',
            VAL_PRIVATE_PART    = 'w',
            VAL_SPECIAL         = 's'
        };

        enum Trust {
            TRUST_UNKNOWN         = 'o',
            TRUST_MISSING_SSIG    = 'i',
            TRUST_DISABLE         = 'd',
            TRUST_REVOKED         = 'r',
            TRUST_EXPIRED         = 'e',
            TRUST_NO_VALUE        = '-',
            TRUST_UNDEFINED       = 'q',
            TRUST_VALID           = 'n',
            TRUST_MARGINAL        = 'm',
            TRUST_FULLY           = 'f',
            TRUST_ULTIMATELY      = 'u',
            TRUST_PRIVATE_PART    = 'w',
            TRUST_SPECIAL         = 's'
        };

        enum KeyScope {
            KEYSCOPE_PUBLIC        = "pub",
            KEYSCOPE_SECRET        = "sec",
            KEYSCOPE_SUB_PUBLIC    = "sub",
            KEYSCOPT_SUB_SECRET    = "ssb"
        };

        enum Capabilities {
            CAP_PRIM_ENCRYPT            = 'E',
            CAP_PRIM_SIGN               = 'S',
            CAP_PRIM_CERTIFY            = 'C',
            CAP_PRIM_AUTHENTIFICATION   = 'A',
            CAP_PRIM_DISABLE            = "D",
            CAP_ENCRYPT                 = 'e',
            CAP_SIGN                    = 's',
            CAP_CERTIFY                 = 'c',
            CAP_AUTHENTIFICATION        = 'a',
            CAP_UNKNOWN                 = '?',
            CAP_NONE                    = "256"
        };

        static QString validityToStr(Validity v);

        explicit Key(Scope s,
                     Algorithm a,
                     unsigned length,
                     Validity v,
                     const QString& id,
                     const QDate& creation,
                     const QDate& expiration,
                     const QString& owner,
                     Validity trust = VAL_NO_VALUE);
        ~Key();

        const QList<Key*>& getSubKeys() const;
        unsigned getLength() const;
        Validity getValidity() const;
        Scope getScope() const;
        const QDate &getExpirationDate() const;
        Validity getTrust() const;

        void addSubKey(Key* k);
        void removeSubKey(Key* k);
        void setExpirationDate(const QDate &dt);

        void addSignature(Signature* s);
        const QList<Signature*>& getSignatures() const;

    private:
        Validity m_val;
        unsigned m_length;
        Scope m_scope;
        QDate m_expiration;
        QList<Signature*> m_sigs;
        Trust m_trust;
};

#endif // KEY_H
