#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QList>

class Key : public QObject {
        Q_OBJECT

    public:
        // doc/DETAILS (src GPG)
        enum Validity {
            UNKNOWN = 'o',
            MISSING_SSIG = 'i',
            REVOKED = 'r',
            EXPIRED = 'e',
            NO_VALUE = '-',
            UNDEFINED = 'q',
            INVALID = 'n',
            MARGINAL = 'm',
            FULLY = 'f',
            ULTIMATELY = 'u',
            PRIVATE_PART = 'w',
            SPECIAL = 's'
        };

        enum Scope {
            PUBLIC, PRIVATE
        };

        enum Algorithm {
            RSA = '1',
            DSA = '2',
            DSA_SIG = '3',
            RSA_SIG = '4'
        };

        enum Capabilities {
            ENCRYPT = 'e',
            SIGN = 's',
            CERTIFY = 'c',
            AUTHENTIFICATION = 'a',
            UNKNOWN = '?'
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
