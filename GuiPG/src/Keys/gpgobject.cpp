#include "gpgobject.h"

QString Key::validityToStr(Validity v) {
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
        case VAL_VALID:
            return "Valide";
        case VAL_MARGINAL:
            return "Marginale";
        case VAL_FULLY:
            return "Complète";
        case VAL_ULTIMATELY:
            return "Ultime";
    }
    return "";
}

GpgObject::GpgObject(QDate creationDate, QString fpr) :
    m_creationDate(creationDate), m_fpr(fpr)
{

}

GpgObject::~GpgObject()
{

}

