#include "gpgobject.h"

QString GpgObject::recordToStr(const QString rec) {
    if (rec == GPG_PUB_KEY)
        return "Clé primaire publique";
    if (rec == GPG_CERT)
        return "crt";
    if (rec == GPG_CERT_AND_PRIVATE)
        return "crs";
    if (rec == GPG_SUB_KEY)
        return "Sous clé publique";
    if (rec == GPG_SECRETE_KEY)
        return "Clé primaire secrète";
    if (rec == GPG_SECRET_SUBKEY)
        return "Sous clé secrète";
    if (rec == GPG_USER_ID)
        return "Identifiant utilisateur";
    if (rec == GPG_USER_ATT)
        return "uat";
    if (rec == GPG_SIGNATURE)
        return "Signature";
    if (rec == GPG_REVOCATION_SIG)
        return "Signature de révocation";
    if (rec == GPG_FINGERPRINT)
        return "Empreinte";
    if (rec == GPG_PUB_KEY_DATA)
        return "pkd";
    if (rec == GPG_KEYGRIP)
        return "grp";
    if (rec == GPG_REVOCATION_KEY)
        return "rvk";
    if (rec == GPG_TRUST_DB)
        return "tru";
    if (rec == GPG_SIG_PACKET)
        return "spk";
    if (rec == GPG_CONFIG_DATA)
        return "cfg";
    return "";
}

QString GpgObject::validityToStr(QString v) {
    if (v == VALIDITY_UNKNOWN)
        return "Inconnue";
    if (v == VALIDITY_MISSING_SSIG)
        return "Invalide (signature manquante)";
    if (v == VALIDITY_DISABLE)
        return "Désactivée";
    if (v == VALIDITY_REVOKED)
        return "Révoquée";
    if (v == VALIDITY_EXPIRED)
        return "Expirée";
    if (v == VALIDITY_NO_VALUE)
        return "Inconnue";
    if (v == VALIDITY_UNDEFINED)
        return "Non définie";
    if (v == VALIDITY_INVALID)
        return "Invalide";
    if (v == VALIDITY_MARGINAL)
        return "Marginale";
    if (v == VALIDITY_FULLY)
        return "Complète";
    if (v == VALIDITY_ULTIMATELY)
        return "Ultime";

    // Ne sais pas vraiment à quoi correspondent les deux suivantes
    if (v == VALIDITY_PRIVATE_PART)
        return "Privée";
    if (v == VALIDITY_SPECIAL)
        return "Spécial";
    return "";
}

QString GpgObject::algoToStr(QString a) {
    if (a == ALGO_RSA)
        return "RSA";
    if (a == ALGO_RSA_E)
        return "RSA - Chiffrement seulement";
    if (a == ALGO_RSA_S)
        return "RSA - Signature seulement";
    if (a == ALGO_ELGAMAL_E)
        return "Elgamal - Chiffrement seulement";
    if (a == ALGO_DSA)
        return "DSA";
    if (a == ALGO_ECDH)
        return "Courbe éliptique Diffie-Hellman";
    if (a == ALGO_ECDSA)
        return "Courbe éliptique DSA";
    if (a == ALGO_ELGAMAL)
        return "Elgamal";
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

QString GpgObject::getValidity() {
    return VALIDITY_EMPTY;
}
