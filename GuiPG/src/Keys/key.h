#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QList>
#include <QDate>
#include "signature.h"

class Key : public Signature {
        Q_OBJECT

    public:
        // doc/DETAILS (src GPG)
        enum Validity {
            VAL_UNKNOWN = 'o',
            VAL_MISSING_SSIG = 'i',
            VAL_REVOKED = 'r',
            VAL_EXPIRED = 'e',
            VAL_NO_VALUE = '-',
            VAL_UNDEFINED = 'q',
            VAL_INVALID = 'n',
            VAL_MARGINAL = 'm',
            VAL_FULLY = 'f',
            VAL_ULTIMATELY = 'u',
            VAL_PRIVATE_PART = 'w',
            VAL_SPECIAL = 's'
        };

        enum Scope {
            SCOPE_PUBLIC, SCOPE_PRIVATE
        };

        enum Capabilities {
            CAP_ENCRYPT = 'e',
            CAP_SIGN = 's',
            CAP_CERTIFY = 'c',
            CAP_AUTHENTIFICATION = 'a',
            CAP_UNKNOWN = '?'
        };

        static QString validityToStr(Validity v);

        explicit Key(Scope s,
                     Algorithm a,
                     unsigned length,
                     Validity v,
                     const QString& id,
                     const QDate& creation,
                     const QDate& expiration,
                     const QString& owner);

        const QList<Key*> getSubKeys() const;
        unsigned getLength() const;
        Validity getValidity() const;
        Scope getScope() const;
        const QDate &getExpirationDate() const;

        void addSubKey(Key* k);
        void removeSubKey(Key* k);
        void setExpirationDate(const QDate &dt);

        void addSignature(Key* k);
        const QList<Key*>& getSignatures() const;

    private:
        QList<Key*> m_subkeys;
        unsigned m_length;
        Validity m_val;
        Scope m_scope;
        QDate m_expiration;
        QList<Key*> m_sigs;
};

#endif // KEY_H
