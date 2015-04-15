#include "signature.h"

// TODO : Mettre des chaines plus parlantes.
QString Signature::sigClassToStr(QString sc) {
    if (sc == SIGCLASS_BINARY)
        return "00";
    if (sc == SIGCLASS_CANONICAL)
        return "01";
    if (sc == SIGCLASS_STANDALONE)
        return "02";
    if (sc == SIGCLASS_GENERIC)
        return "10";
    if (sc == SIGCLASS_PERSONA)
        return "11";
    if (sc == SIGCLASS_CASUAL)
        return "12";
    if (sc == SIGCLASS_POSITIVE)
        return "13";
    if (sc == SIGCLASS_SUBKEY)
        return "18";
    if (sc == SIGCLASS_PRIMARY)
        return "19";
    if (sc == SIGCLASS_DIRECTLY)
        return "1F";
    if (sc == SIGCLASS_KEY_REVOCATION)
        return "20";
    if (sc == SIGCLASS_SUBKEY_REVOCATION)
        return "28";
    if (sc == SIGCLASS_CERT_REVOCATION)
        return "30";
    if (sc == SIGCLASS_TIMESTAMP)
        return "40";
    if (sc == SIGCLASS_THIRD_PARTY)
        return "50";
    return "";
}

QString Signature::sigScopeToStr(QString ss) {
    if (ss == SIGSCOPE_LOCAL)
        return "Locale";
    if (ss == SIGSCOPE_EXPORTABLE)
        return "Exportable";
    return "";
}

QString Signature::hashAlgoToStr(QString ha) {
    if (ha == HASH_ALGO_SHA1)
        return "SHA-1";
    if (ha == HASH_ALGO_SHA256)
        return "SHA-256";
    return "";
}

Signature::Signature(QString algo,
                     QString keyId,
                     QDate creationDate,
                     QString uid,
                     QString sigClass,
                     QString sigScope,
                     QString hashAlgo,
                     QString fpr) : GpgObject (creationDate, fpr)
{
    m_algo = algo;
    m_keyId = keyId;
    m_creationDate = creationDate;
    m_uid = uid;
    m_sigClass = sigClass;
    m_sigScope = sigScope;
    m_hashAlgo = hashAlgo;
}

QString Signature::getAlgo() const {
    return m_algo;
}

QString Signature::getKeyId() const {
    return m_keyId;
}

QString Signature::getUid() const {
    return m_uid;
}

QString Signature::getSigClass() const {
    return m_sigClass;
}

QString Signature::getSigScope() const {
    return m_sigScope;
}

QString Signature::getHashAlgo() const {
    return m_hashAlgo;
}
