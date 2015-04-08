#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QObject>
#include <QDate>
#include "gpgobject.h"
#include "uid.h"

class Signature : public GpgObject {
    Q_OBJECT

    public:

        enum SigClass {
            SIGCLASS_BINARY             = "00",
            SIGCLASS_CANONICAL          = "01",
            SIGCLASS_STANDALONE         = "02",
            SIGCLASS_GENERIC            = "10",
            SIGCLASS_PERSONA            = "11",
            SIGCLASS_CASUAL             = "12",
            SIGCLASS_POSITIVE           = "13",
            SIGCLASS_SUBKEY             = "18",
            SIGCLASS_PRIMARY            = "19",
            SIGCLASS_DIRECTLY           = "1F",
            SIGCLASS_KEY_REVOCATION     = "20",
            SIGCLASS_SUBKEY_REVOCATION  = "28",
            SIGCLASS_CERT_REVOCATION    = "30",
            SIGCLASS_TIMESTAMP          = "40",
            SIGCLASS_THIRD_PARTY        = "50"
        };

        enum SigScope {
            SIGSCOPE_LOCAL  = "l",
            SIGSCOPE_EXPORT = "x"
        };

        enum HashAlgo {
            HASH_ALGO_SHA1    = 2,
            HASH_ALGO_SHA256  = 8
        };

        explicit Signature(PubkeyAlgo pubAlgo,
                           QString keyId,
                           QDate creationDate,
                           Uid uid,
                           SigClass sigclass,
                           HashAlgo hashAlgo);

        const Uid getUid() const;
        const SigClass getSigClass() const;
        const HashAlgo getHashAlgo() const;

    signals:

    public slots:

    private:
        Uid m_uid;
        SigClass m_sigClass;
        HashAlgo m_hashAlgo;
};

#endif // SIGNATURE_H
