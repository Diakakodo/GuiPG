#ifndef PRIMASECKEY_H
#define PRIMASECKEY_H

#include "subseckey.h"
#include "uid.h"
class PrimaPubKey;

class PrimaSecKey : public SubSecKey {
    Q_OBJECT

    public:

        PrimaSecKey(const QString keyScope,
                    const unsigned length,
                    const QString algo,
                    const QString keyId,
                    const QDate creationDate,
                    const QDate expirationDate,
                    QString fpr = ""
                    );
        ~PrimaSecKey();

        QDate getExpirationDate() const;
        Uid* getUid() const;
        const QList<SubSecKey*> getSubSecKeyList() const;

        void setUid(Uid *uid);
        void addSubSecKey(SubSecKey* subSecKey);
        void setPrimaryPubKey(PrimaPubKey* pub);
        PrimaPubKey* getPrimarySecKey();
        bool hasPrimaSecKey();

    private:

        QDate m_expirationDate;
        Uid* m_uid = nullptr;
        QList<SubSecKey*> m_subSecKeyList;
        PrimaPubKey* m_pub = nullptr;


};

#endif // PRIMASECKEY_H
