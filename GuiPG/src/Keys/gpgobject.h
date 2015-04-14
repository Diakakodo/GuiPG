#ifndef GPGOBJECT_H
#define GPGOBJECT_H

#include <QObject>
#include <QDate>

// Type d'enregistrement, sert aussi pour KeyScope
#define GPG_PUB_KEY             "pub"
#define GPG_CERT                "crt"
#define GPG_CERT_AND_PRIVATE    "crs"
#define GPG_SUB_KEY             "sub"
#define GPG_SECRETE_KEY         "sec"
#define GPG_SECRET_SUBKEY       "ssb"
#define GPG_USER_ID             "uid"
#define GPG_USER_ATT            "uat"
#define GPG_SIGNATURE           "sig"
#define GPG_REVOCATION_SIG      "rev"
#define GPG_FINGERPRINT         "fpr"
#define GPG_PUB_KEY_DATA        "pkd"
#define GPG_KEYGRIP             "grp"
#define GPG_REVOCATION_KEY      "rvk"
#define GPG_TRUST_DB            "tru"
#define GPG_SIG_PACKET          "spk"
#define GPG_CONFIG_DATA         "cfg"

// Validity
#define VALIDITY_EMPTY          ""
#define VALIDITY_UNKNOWN        "o"
#define VALIDITY_MISSING_SSIG   "i"
#define VALIDITY_DISABLE        "d"
#define VALIDITY_REVOKED        "r"
#define VALIDITY_EXPIRED        "e"
#define VALIDITY_NO_VALUE       "-"
#define VALIDITY_UNDEFINED      "q"
#define VALIDITY_INVALID        "n"
#define VALIDITY_MARGINAL       "m"
#define VALIDITY_FULLY          "f"
#define VALIDITY_ULTIMATELY     "u"
#define VALIDITY_PRIVATE_PART   "w"
#define VALIDITY_SPECIAL        "s"

#define ALGO_RSA        "1"
#define ALGO_RSA_E      "2"
#define ALGO_RSA_S      "3"
#define ALGO_ELGAMAL_E  "16"
#define ALGO_DSA        "17"
#define ALGO_ECDH       "18"
#define ALGO_ECDSA      "19"
#define ALGO_ELGAMAL    "20"

class GpgObject : public QObject {
    Q_OBJECT

    public:

        static QString recordToStr(const QString rec);
        static QString validityToStr(QString v);
        static QString algoToStr(QString a);

        explicit GpgObject(const QDate creationDate, QString fpr = "");
        virtual ~GpgObject() = 0;

        virtual QString getValidity();

        QDate getCreationDate() const;
        QString getFpr() const;

        void setFpr(QString fpr);

    protected:
        QDate m_creationDate;
        QString m_fpr;

    signals:

    public slots:
};

#endif // GPGOBJECT_H
