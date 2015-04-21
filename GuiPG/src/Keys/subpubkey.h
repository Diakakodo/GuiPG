#ifndef SUBPUBKEY_H
#define SUBPUBKEY_H

#include "pubkey.h"

class SubPubKey : public PubKey {
    Q_OBJECT

    public:
        SubPubKey(const QString keyScope,
                  const QString validity,
                  const unsigned length,
                  const QString algo,
                  const QString keyId,
                  const QDate creationDate,
                  const QDate expirationDate,
                  const QString capabilities,
                  QString fpr = "");
        ~SubPubKey();
        void setSubSecKey(SubSecKey* ssb);
        SubSecKey* getSubSecKey() const;
        bool hasSubSecKey();

    private:
        SubSecKey* m_ssb = nullptr;
};

#endif // SUBPUBKEY_H
