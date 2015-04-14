#include "signature.h"

// TODO : Mettre des chaines plus parlantes.
static QString Signature::sigClassToStr(SigClass sc) {
    switch(sc) {
        case SIGCLASS_BINARY:
            return "00";
        case SIGCLASS_CANONICAL:
            return "01";
        case SIGCLASS_STANDALONE:
            return "02";
        case SIGCLASS_GENERIC:
            return "10";
        case SIGCLASS_PERSONA:
            return "11";
        case SIGCLASS_CASUAL:
            return "12";
        case SIGCLASS_POSITIVE:
            return "13";
        case SIGCLASS_SUBKEY:
            return "18";
        case SIGCLASS_PRIMARY:
            return "19";
        case SIGCLASS_DIRECTLY:
            return "1F";
        case SIGCLASS_KEY_REVOCATION:
            return "20";
        case SIGCLASS_SUBKEY_REVOCATION:
            return "28";
        case SIGCLASS_CERT_REVOCATION:
            return "30";
        case SIGCLASS_TIMESTAMP:
            return "40";
        case SIGCLASS_THIRD_PARTY:
            return "50";
    }
    return "";
}

static QString Signature::sigScopeToStr(SigScope ss) {
    switch (ss) {
        case SIGSCOPE_LOCAL:
            return "Locale";
        case SIGSCOPE_EXPORTABLE:
            return "Exportable";
    }
    return "";
}

static QString Signature::hashAlgoToStr(HashAlgo ha) {
    switch (ha) {
        case HASH_ALGO_SHA1:
            return "SHA-1";
        case HASH_ALGO_SHA256:
            return "SHA-256";
    }
    return "";
}

Signature::Signature(const Algorithm algo,
                     const QString keyId,
                     const QDate creationDate,
                     const Uid uid,
                     const SigClass sigClass,
                     const HashAlgo hashAlgo,
                     QString fpr) : GpgObject (creationDate,
                                               fpr),
                      m_algo(algo),
                      m_keyId(keyId),
                      m_creationDate(creationDate),
                      m_uid(uid),
                      m_sigClass(sigClass),
                      m_hashAlgo(hashAlgo)
{}

GpgObject::Algorithm Signature::getAlgo() const {
    return m_algo;
}

QString Signature::getKeyId() const {
    return m_keyId;
}

Uid Signature::getUid() const {
    return m_uid;
}

Signature::SigClass Signature::getSigClass() const {
    return m_sigClass;
}

Signature::SigScope Signature::getSigScope() const {
    return m_sigScope;
}

Signature::HashAlgo Signature::getHashAlgo() const {
    return m_hashAlgo;
}
