#ifndef SUBSECKEY_H
#define SUBSECKEY_H

#include <QObject>
#include <QList>
#include <QDate>
#include "gpgobject.h"

class SubSecKey : public GpgObject {
    Q_OBJECT

    public:

        enum KeyScope {
            KEYSCOPE_PUBLIC        = REC_PUB_KEY,
            KEYSCOPE_SECRET        = REC_SECRETE_KEY,
            KEYSCOPE_SUB_PUBLIC    = REC_SUB_KEY,
            KEYSCOPT_SUB_SECRET    = REC_SECRET_SUBKEY
        };

        explicit SubSecKey(const KeyScope keyScope,
                     const unsigned length,
                     const Algorithm algo,
                     const QString keyId,
                     const QDate creationDate,
                     QString fpr = ""
                     );
        ~SubSecKey();

        KeyScope getKeyScope() const;
        unsigned getLength() const;
        Algorithm getAlgo() const;
        QString getKeyId() const;
        Validity getValidity();

    private:
        const KeyScope m_keyScope;
        const unsigned m_length;
        const Algorithm m_algo;
        const QString m_keyId;
};

#endif // SUBSECKEY_H
