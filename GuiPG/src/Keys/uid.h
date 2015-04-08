#ifndef UID_H
#define UID_H

#include <QObject>
#include "signature.h"

class Uid : public QObject {
    Q_OBJECT

    public:

        enum CipherAlgo {
            CIPHER_ALGO_NONE        = "S0",
            CIPHER_ALGO_IDEA        = "S1",
            CIPHER_ALGO_3DES        = "S2",
            CIPHER_ALGO_CAST5       = "S3",
            CIPHER_ALGO_BLOWFISH    = "S4",
            CIPHER_ALGO_AES         = "S7",
            CIPHER_ALGO_AES192      = "S8",
            CIPHER_ALGO_AES256      = "S9",
            CIPHER_ALGO_TWOFISH     = "S10",
            CIPHER_ALGO_CAMELLIA128 = "S11",
            CIPHER_ALGO_CAMELLIA192 = "S12",
            CIPHER_ALGO_CAMELLIA256 = "S13"
        };

        enum DigestAlgo {
            DIGEST_ALGO_MD5     = "H1",
            DIGEST_ALGO_SHA1    = "H2",
            DIGEST_ALGO_RMD160  = "H3",
            DIGEST_ALGO_SHA256  = "H8",
            DIGEST_ALGO_SHA384  = "H9",
            DIGEST_ALGO_SHA512  = "H10",
            DIGEST_ALGO_SHA224  = "H11"
        };

        enum CompressAlgo {
            COMPRESS_ALGO_NONE  = "Z0",
            COMPRESS_ALGO_ZIP   = "Z1",
            COMPRESS_ALGO_ZLIB  = "Z2",
            COMPRESS_ALGO_BZIP2 = "Z3"
        };

        Uid(QString name, QString comment, QString mail);
        ~Uid();

        const QString getName() const;
        const QString getComment() const;
        const QString getMail() const;
        const QList<Signature*>& getSigList() const;

        void addSignature(Signature* sig);

    private:
        QString m_name;
        QString m_comment;
        QString m_mail;
        QList<Signature*> m_sigList;
};

#endif // UID_H
