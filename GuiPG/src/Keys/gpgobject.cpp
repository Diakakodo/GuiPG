#include "gpgobject.h"

QString GpgObject::recordToStr(Record r) {
    switch (r) {
        case REC_PUB_KEY:
            return "pub";
        case REC_CERT:
            return "crt";
        case REC_CERT_AND_PRIVATE:
            return "crs";
        case REC_SUB_KEY:
            return "sub";
        case REC_SECRETE_KEY:
            return "sec";
        case REC_SECRET_SUBKEY:
            return "ssb";
        case REC_USER_ID:
            return "uid";
        case REC_USER_ATT:
            return "uat";
        case REC_SIGNATURE:
            return "sig";
        case REC_REVOCATION_SIG:
            return "rev";
        case REC_FINGERPRINT:
            return "fpr";
        case REC_PUB_KEY_DATA:
            return "pkd";
        case REC_KEYGRIP:
            return "grp";
        case REC_REVOCATION_KEY:
            return "rvk";
        case REC_TRUST_DB:
            return "tru";
        case REC_SIG_PACKET:
            return "spk";
        case REC_CONFIG_DATA:
            return "cfg";
    }
    return "";
}

QString GpgObject::validityToStr(Validity v) {
    switch (v) {
        case VAL_UNKNOWN:
            return "Inconnue";
        case VAL_MISSING_SSIG:
            return "Invalide (signature manquante)";
        case VAL_DISABLE:
            return "Désactivée";
        case VAL_REVOKED:
            return "Révoquée";
        case VAL_EXPIRED:
            return "Expirée";
        case VAL_NO_VALUE:
            return "Inconnue";
        case VAL_UNDEFINED:
            return "Non définie";
        case VAL_INVALID:
            return "Invalide";
        case VAL_MARGINAL:
            return "Marginale";
        case VAL_FULLY:
            return "Complète";
        case VAL_ULTIMATELY:
            return "Ultime";
    }

    return "";
}

QString GpgObject::algoToStr(Algorithm a) {
    switch (a) {
        case ALGO_RSA:
            return "RSA";
        case ALGO_RSA_E:
            return "RSA - Chiffrement seulement";
        case ALGO_RSA_S:
            return "RSA - Signature seulement";
        case ALGO_ELGAMAL_E:
            return "Elgamal - Chiffrement seulement";
        case ALGO_DSA:
            return "DSA";
        case ALGO_ECDH:
            return "Courbe éliptique Diffie-Hellman";
        case ALGO_ECDSA:
            return "Courbe éliptique DSA";
        case ALGO_ELGAMAL:
            return "Elgamal";
    }
    return "";
}

GpgObject::GpgObject(const QDate creationDate, QString fpr) :
    m_creationDate(creationDate), m_fpr(fpr) {}

GpgObject::~GpgObject() {}

QDate GpgObject::getCreationDate() const {
    return m_creationDate;
}

QString GpgObject::getFpr() const {
    return m_fpr;
}

void GpgObject::setFpr(QString fpr) {
    m_fpr = fpr;
}

GpgObject::Validity GpgObject::getValidity() {
    return Validity::VAL_NO_VALUE;
}
