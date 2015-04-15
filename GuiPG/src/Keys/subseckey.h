#ifndef SUBSECKEY_H
#define SUBSECKEY_H

#include <QObject>
#include <QList>
#include <QDate>
#include "gpgobject.h"

class SubSecKey : public GpgObject {
    Q_OBJECT

    public:

        explicit SubSecKey(const QString keyScope,
                     const unsigned length,
                     const QString algo,
                     const QString keyId,
                     const QDate creationDate,
                     QString fpr = ""
                     );
        ~SubSecKey();

        QString getKeyScope() const;
        unsigned getLength() const;
        QString getAlgo() const;
        QString getKeyId() const;
        QString getValidity();

    protected:
        const QString m_keyScope;
        const unsigned m_length;
        const QString m_algo;
        const QString m_keyId;
};

#endif // SUBSECKEY_H
