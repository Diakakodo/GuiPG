#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>
#include "primapubkey.h"
#include "../GPG/gpgmanager.h"

class KeyManager : public QObject {
    Q_OBJECT

    public:
        explicit KeyManager(Profile *p);
        ~KeyManager();

        void load();
        const QList<PrimaPubKey *> &getPubKeys() const;

    signals:
        void PubKeysLoaded();

    private slots:
        void loadSecretKeys();

    private:
        void gpgFinishedPublicKeys(int s, const QString& output);
        void gpgFinishedSecretKeys(int s, const QString& output);
        QDate strToDate(const QString& d) const;

        QList<PrimaPubKey*> m_primaPubKeys;
        GPGManager* m_gpg;
};

#endif // KEYMANAGER_H
