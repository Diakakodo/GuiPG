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
            SIGCLASS_BINARY             = 0,    // 00
            SIGCLASS_CANONICAL          = 1,    // 01
            SIGCLASS_STANDALONE         = 2,    // 02
            SIGCLASS_GENERIC            = 16,   // 10
            SIGCLASS_PERSONA            = 17,   // 11
            SIGCLASS_CASUAL             = 18,   // 12
            SIGCLASS_POSITIVE           = 19,   // 13
            SIGCLASS_SUBKEY             = 24,   // 18
            SIGCLASS_PRIMARY            = 25,   // 19
            SIGCLASS_DIRECTLY           = 31,   // 1F
            SIGCLASS_KEY_REVOCATION     = 32,   // 20
            SIGCLASS_SUBKEY_REVOCATION  = 40,   // 28
            SIGCLASS_CERT_REVOCATION    = 48,   // 30
            SIGCLASS_TIMESTAMP          = 64,   // 40
            SIGCLASS_THIRD_PARTY        = 80    // 50
        };

        enum SigScope {
            SIGSCOPE_LOCAL      = 'l',
            SIGSCOPE_EXPORTABLE = 'x'
        };

        enum HashAlgo {
            HASH_ALGO_SHA1    = 2,
            HASH_ALGO_SHA256  = 8
        };

        static QString sigClassToStr(SigClass sc);

        explicit Signature(PubkeyAlgo pubAlgo,
                           QString keyId,
                           QDate creationDate,
                           Uid uid,
                           SigClass sigclass,
                           HashAlgo hashAlgo);

        const Algorithme getAlgo() const;
        const QString getKeyId() const;
        const Uid getUid() const;
        const SigClass getSigClass() const;
        const SigScope getSigScope() const;
        const HashAlgo getHashAlgo() const;

    signals:

    public slots:

    private:
        Algorithme m_algo;
        QString m_keyId;
        Uid m_uid;
        SigClass m_sigClass;
        SigScope m_sigScope;
        HashAlgo m_hashAlgo;
};

#endif // SIGNATURE_H
