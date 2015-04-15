#include "uid.h"

QString Uid::cipherToStr(QString cipherAlgo) {
    // TODO
    return "";
}

QString Uid::digestToStr(QString digestAlgo) {
    // TODO
    return "";
}

QString Uid::compressToStr(QString compressAlgo) {
    // TODO
    return "";
}

Uid::Uid(QString validity,
         QDate creationDate,
         QString fpr,
         QString name,
         QString mail) : GpgObject (creationDate,
                                    fpr),
            m_validity(validity),
            m_name(name),
            m_mail(mail)
{}

Uid::~Uid()
{

}

QString Uid::getValidity() const {
    return m_validity;
}

QString Uid::getName() const {
    return m_name;
}

QString Uid::getMail() const {
    return m_mail;
}

const QList<Signature*> Uid::getSigList() const {
    return m_sigList;
}

void Uid::addSignature(Signature* sig) {
    m_sigList.append(sig);
}
