#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QObject>
#include <QList>
#include "key.h"
#include "../GPG/gpgmanager.h"

class KeyManager : public QObject {
        Q_OBJECT

    public:
        explicit KeyManager(const Profile* p);
        ~KeyManager();

    private:
        QList<Key*> m_keys;
        GPGManager* m_gpg;
};

#endif // KEYMANAGER_H
