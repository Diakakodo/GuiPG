#ifndef PUBLICKEY_H
#define PUBLICKEY_H

#include "key.h"


class PublicKey {
    Q_OBJECT

    public:
        PublicKey();
        ~PublicKey();

    private:
        QList<Key*> m_subkeys;
};

#endif // PUBLICKEY_H
