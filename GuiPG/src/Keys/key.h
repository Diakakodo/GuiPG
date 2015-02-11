#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QList>
#include <QDateTime>

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
            ALGO_RSA = '1',
            ALGO_DSA = '2',
            ALGO_DSA_SIG = '3',
            ALGO_RSA_SIG = '4'
        };

        enum Capabilities {
            CAP_ENCRYPT = 'e',
            CAP_SIGN = 's',
            CAP_CERTIFY = 'c',
            CAP_AUTHENTIFICATION = 'a',
            CAP_UNKNOWN = '?'
        };

        explicit Key(Scope s,
                     Algorithm a,
                     unsigned length,
                     Validity v,
                     const QString& id,
                     const QDateTime& creation,
                     const QDateTime& expiration,
                     const QString& owner,
                     const QString& comment,
                     const QString& email,
                     unsigned uid);

        const QList<Key*> getSubKeys() const;
        unsigned getLength() const;
        Validity getValidity() const;
        Scope getScope() const;
        Algorithm getAlgorithm() const;
        const QString& getId() const;
        const QDateTime& getCreationDate() const;
        const QDateTime& getExpirationDate() const;
        const QString& getOwner() const;
        const QString& getComment() const;
        const QString& getEmail() const;
        unsigned getUserId() const;

        void addSubKey(Key* k);
        void removeSubKey(Key* k);
        void setExpirationDate(const QDateTime& dt);

    private:
        QList<Key*> m_subkeys;
        unsigned m_length;
        Validity m_val;
        Scope m_scope;
        Algorithm m_algo;
        QString m_id;
        QDateTime m_creation;
        QDateTime m_expiration;
        QString m_owner;
        QString m_comment;
        QString m_email;
        unsigned m_uid;
};

#endif // KEY_H
