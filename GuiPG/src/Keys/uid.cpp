#include "uid.h"

Uid::Uid(const Validity validity,
         const QDate creationDate,
         const QString fpr,
         const QString name,
         const QString comment,
         const QString mail) : GpgObject (creationDate,
                                    fpr),
            m_validity(validity),
            m_name(name),
            m_comment(comment),
            m_mail(mail)
{}

Uid::~Uid()
{

}

GpgObject::Validity Uid::getValidity() const {
    return m_validity;
}

QString Uid::getName() const {
    return m_name;
}

QString Uid::getComment() const {
    return m_comment;
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
