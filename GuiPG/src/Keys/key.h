#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QList>
#include <QDate>

class Key : public QObject {
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

        enum Algorithm {
            ALGO_RSA,
            ALGO_DSA,
            ALGO_DSA_SIG,
            ALGO_RSA_SIG
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
        Algorithm getAlgorithm() const;
        const QString& getId() const;
        const QDate& getCreationDate() const;
        const QDate &getExpirationDate() const;
        const QString& getOwner() const;

        void addSubKey(Key* k);
        void removeSubKey(Key* k);
        void setExpirationDate(const QDate &dt);

    private:
        QList<Key*> m_subkeys;
        unsigned m_length;
        Validity m_val;
        Scope m_scope;
        Algorithm m_algo;
        QString m_id;
        QDate m_creation;
        QDate m_expiration;
        QString m_owner;
        unsigned m_uid;
};

#endif // KEY_H
