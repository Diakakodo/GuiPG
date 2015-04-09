#ifndef GPGOBJECT_H
#define GPGOBJECT_H

#include <QObject>

class GpgObject : public QObject {
    Q_OBJECT

    public:

        enum Record {
            REC_PUB_KEY             = 1,    // pub
            REC_CERT                = 2,    // crt
            REC_CERT_AND_PRIVATE    = 3,    // crs
            REC_SUB_KEY             = 4,    // sub
            REC_SECRETE_KEY         = 5,    // sec
            REC_SECRET_SUBKEY       = 6,    // ssb
            REC_USER_ID             = 7,    // uid
            REC_USER_ATT            = 8,    // uat
            REC_SIGNATURE           = 9,    // sig
            REC_REVOCATION_SIG      = 10,   // rev
            REC_FINGERPRINT         = 11,   // fpr
            REC_PUB_KEY_DATA        = 12,   // pkd
            REC_KEYGRIP             = 13,   // grp
            REC_REVOCATION_KEY      = 14,   // rvk
            REC_TRUST_DB            = 15,   // tru
            REC_SIG_PACKET          = 16,   // spk
            REC_CONFIG_DATA         = 17    // cfg
        };

        enum Validity {
            VAL_UNKNOWN         = 'o',
            VAL_MISSING_SSIG    = 'i',
            VAL_DISABLE         = 'd',
            VAL_REVOKED         = 'r',
            VAL_EXPIRED         = 'e',
            VAL_NO_VALUE        = '-',
            VAL_UNDEFINED       = 'q',
            VAL_INVALID         = 'n',
            VAL_MARGINAL        = 'm',
            VAL_FULLY           = 'f',
            VAL_ULTIMATELY      = 'u',
            VAL_PRIVATE_PART    = 'w',
            VAL_SPECIAL         = 's'
        };

        enum Algorithm {
            ALGO_RSA        = 1,
            ALGO_RSA_E      = 2,
            ALGO_RSA_S      = 3,
            ALGO_ELGAMAL_E  = 16,
            ALGO_DSA        = 17,
            ALGO_ECDH       = 18,
            ALGO_ECDSA      = 19,
            ALGO_ELGAMAL    = 20
        };

        static QString recordToStr(Record r);
        static QString validityToStr(Validity v);
        static QString algoToStr(Algorithm a);

        explicit GpgObject(const QDate creationDate, QString fpr = "");
        virtual ~GpgObject() = 0;

        QDate getCreationDate() const;
        QString getFpr() const;

        void setFpr(QString fpr);

    protected:
        const QDate m_creationDate;
        QString m_fpr;

    signals:

    public slots:
};

#endif // GPGOBJECT_H
