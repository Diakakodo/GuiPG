#ifndef UID_H
#define UID_H

#include <QObject>
#include "gpgobject.h"
class Signature;

class Uid : public GpgObject {
    Q_OBJECT

    public:

        enum CipherAlgo {
            CIPHER_ALGO_NONE        = 0, // S0
            CIPHER_ALGO_IDEA        = 1, // S1
            CIPHER_ALGO_3DES        = 2, // S2
            CIPHER_ALGO_CAST5       = 3, // S3
            CIPHER_ALGO_BLOWFISH    = 4, // S4
            CIPHER_ALGO_AES         = 7, // S7
            CIPHER_ALGO_AES192      = 8, // S8
            CIPHER_ALGO_AES256      = 9, // S9
            CIPHER_ALGO_TWOFISH     = 10,// S10
            CIPHER_ALGO_CAMELLIA128 = 11,// S11
            CIPHER_ALGO_CAMELLIA192 = 12,// S12
            CIPHER_ALGO_CAMELLIA256 = 13 // S13
        };

        enum DigestAlgo {
            DIGEST_ALGO_MD5     = 1, // H1
            DIGEST_ALGO_SHA1    = 2, // H2
            DIGEST_ALGO_RMD160  = 3, // H3
            DIGEST_ALGO_SHA256  = 8, // H8
            DIGEST_ALGO_SHA384  = 9, // H9
            DIGEST_ALGO_SHA512  = 10,// H10
            DIGEST_ALGO_SHA224  = 11 // H11
        };

        enum CompressAlgo {
            COMPRESS_ALGO_NONE  = 0, // Z0
            COMPRESS_ALGO_ZIP   = 1, // Z1
            COMPRESS_ALGO_ZLIB  = 2, // Z2
            COMPRESS_ALGO_BZIP2 = 3  // Z3
        };

        static QString cipherToStr(CipherAlgo cipherAlgo);
        static QString digestToStr(DigestAlgo digestAlgo);
        static QString compressToStr(CompressAlgo compressAlgo);

        Uid(const Validity validity = 0,
            const QDate creationDate,
            const QString fpr,
            const QString name,
            const QString comment,
            const QString mail);
        ~Uid();

        Validity getValidity() const;
        QString getName() const;
        QString getComment() const;
        QString getMail() const;
        const QList<Signature*> getSigList() const;

        void addSignature(Signature* sig);

    private:
        const Validity m_validity;
        const QString m_name;
        const QString m_comment;
        const QString m_mail;
        QList<Signature*> m_sigList;
};

#endif // UID_H
