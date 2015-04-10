#ifndef PRIMASECKEY_H
#define PRIMASECKEY_H

#include "subseckey.h"
#include "uid.h"

class PrimaSecKey : public SubSecKey {
    Q_OBJECT

    public:

        PrimaSecKey(const KeyScope keyScope,
                    const unsigned length,
                    const Algorithm algo,
                    const QString keyId,
                    const QDate creationDate,
                    const QDate expirationDate,
                    QString fpr = ""
                    );
        ~PrimaSecKey();

        QDate getExpirationDate() const;
        Uid getUid() const;
        const QList<SubSecKey*> getSubSecKeyList() const;

        void addUid(Uid uid);
        void addSubSecKey(SubSecKey* subSecKey);

    private:

        const QDate m_expirationDate;
        Uid m_uid;
        QList<SubSecKey*> m_subSecKeyList;


};

#endif // PRIMASECKEY_H
