#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QObject>
#include <QDate>
#include "gpgobject.h"
#include "uid.h"

#define SIGCLASS_BINARY             "00"
#define SIGCLASS_CANONICAL          "01"
#define SIGCLASS_STANDALONE         "02"
#define SIGCLASS_GENERIC            "10"
#define SIGCLASS_PERSONA            "11"
#define SIGCLASS_CASUAL             "12"
#define SIGCLASS_POSITIVE           "13"
#define SIGCLASS_SUBKEY             "18"
#define SIGCLASS_PRIMARY            "19"
#define SIGCLASS_DIRECTLY           "1F"
#define SIGCLASS_KEY_REVOCATION     "20"
#define SIGCLASS_SUBKEY_REVOCATION  "28"
#define SIGCLASS_CERT_REVOCATION    "30"
#define SIGCLASS_TIMESTAMP          "40"
#define SIGCLASS_THIRD_PARTY        "50"

#define SIGSCOPE_LOCAL      "l"
#define SIGSCOPE_EXPORTABLE "x"

#define HASH_ALGO_SHA1    "2"
#define HASH_ALGO_SHA256  "8"

class Signature : public GpgObject {
    Q_OBJECT

    public:

        static QString sigClassToStr(QString sc);
        static QString sigScopeToStr(QString ss);
        static QString hashAlgoToStr(QString ha);

        explicit Signature(QString algo,
                           QString keyId,
                           QDate creationDate,
                           QString uid,
                           QString sigClass,
                           QString sigScope,
                           QString hashAlgo,
                           QString fpr = "");

        QString getAlgo() const;
        QString getKeyId() const;
        QString getUid() const;
        QString getSigClass() const;
        QString getSigScope() const;
        QString getHashAlgo() const;

    signals:

    public slots:

    private:
        QString m_algo;
        QString m_keyId;
        QString m_uid;
        QString m_sigClass;
        QString m_sigScope;
        QString m_hashAlgo;
        QDate m_creationDate;
};

#endif // SIGNATURE_H
