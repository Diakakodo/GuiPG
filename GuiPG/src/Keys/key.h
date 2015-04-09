#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QList>
#include <QDate>
#include "gpgobject.h"

class Key : public GpgObject {
    Q_OBJECT

    public:

        enum KeyScope {
            KEYSCOPE_PUBLIC        = REC_PUB_KEY,
            KEYSCOPE_SECRET        = REC_SECRETE_KEY,
            KEYSCOPE_SUB_PUBLIC    = REC_SUB_KEY,
            KEYSCOPT_SUB_SECRET    = REC_SECRET_SUBKEY
        };

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

        explicit Key(const KeyScope keyScope,
                     const Validity validity,
                     const unsigned length,
                     const Algorithm algo,
                     const QString keyId,
                     const QDate creationDate,
                     const QDate expirationDate,
                     const QString capabilities,
                     QString fpr = ""
                     );
        virtual ~Key() = 0;

        KeyScope getKeyScope() const;
        Validity getValidity() const;
        unsigned getLength() const;
        Algorithm getAlgo() const;
        QString getKeyId() const;
        QDate getExpirationDate() const;
        QString getCapabilities() const;

    private:
        KeyScope m_keyScope;
        Validity m_validity;
        unsigned m_length;
        Algorithm m_algo;
        QString m_keyId;
        QDate m_expirationDate;
        QString m_capabilities;
};

#endif // KEY_H
