#ifndef GPGOBJECT_H
#define GPGOBJECT_H

#include <QObject>

class GpgObject : public QObject {
    Q_OBJECT

    public:

        enum PubkeyAlgo {
            PUBKEY_ALGO_RSA        = 1,
            PUBKEY_ALGO_RSA_E      = 2,
            PUBKEY_ALGO_RSA_S      = 3,
            PUBKEY_ALGO_ELGAMAL_E  = 16,
            PUBKEY_ALGO_DSA        = 17,
            PUBKEY_ALGO_ECDH       = 18,
            PUBKEY_ALGO_ECDSA      = 19,
            PUBKEY_ALGO_ELGAMAL    = 20
        };

        explicit GpgObject(PubkeyAlgo pubAlgo, QString keyId, QDate creationDate);
        ~GpgObject();

        const PubkeyAlgo getPubkeyAlgo() const;
        const QString getKeyId() const;
        const QDate getCreationDate() const;

    protected:
        PubkeyAlgo m_pubAlgo;
        QString m_keyId;
        QDate m_creationDate;

    signals:

    public slots:
};

#endif // GPGOBJECT_H
