#ifndef UID_H
#define UID_H

#include <QObject>
#include "gpgobject.h"
class Signature;

#define CIPHER_ALGO_NONE        "S0"
#define CIPHER_ALGO_IDEA        "S1"
#define CIPHER_ALGO_3DES        "S2"
#define CIPHER_ALGO_CAST5       "S3"
#define CIPHER_ALGO_BLOWFISH    "S4"
#define CIPHER_ALGO_AES         "S7"
#define CIPHER_ALGO_AES192      "S8"
#define CIPHER_ALGO_AES256      "S9"
#define CIPHER_ALGO_TWOFISH     "S10"
#define CIPHER_ALGO_CAMELLIA128 "S11"
#define CIPHER_ALGO_CAMELLIA192 "S12"
#define CIPHER_ALGO_CAMELLIA256 "S13"

#define DIGEST_ALGO_MD5     "H1"
#define DIGEST_ALGO_SHA1    "H2"
#define DIGEST_ALGO_RMD160  "H3"
#define DIGEST_ALGO_SHA256  "H8"
#define DIGEST_ALGO_SHA384  "H9"
#define DIGEST_ALGO_SHA512  "H10"
#define DIGEST_ALGO_SHA224  "H11"

#define COMPRESS_ALGO_NONE  "Z0"
#define COMPRESS_ALGO_ZIP   "Z1"
#define COMPRESS_ALGO_ZLIB  "Z2"
#define COMPRESS_ALGO_BZIP2 "Z3"

class Uid : public GpgObject {
    Q_OBJECT

    public:

        static QString cipherToStr(QString cipherAlgo);
        static QString digestToStr(QString digestAlgo);
        static QString compressToStr(QString compressAlgo);

        Uid(QString validity,
            QDate creationDate,
            QString fpr,
            QString name,
            QString comment,
            QString mail);
        ~Uid();

        QString getValidity() const;
        QString getName() const;
        QString getComment() const;
        QString getMail() const;
        QString getPref() const;
        const QList<Signature*> getSigList() const;

        void addSignature(Signature* sig);

    private:
        QString m_validity;
        QString m_name;
        QString m_comment;
        QString m_mail;
        QString m_pref;
        QList<Signature*> m_sigList;
};

#endif // UID_H
