#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>
#include "primapubkey.h"
#include "primaseckey.h"
#include "../GPG/gpgmanager.h"

class KeyManager : public QObject {
    Q_OBJECT

    public:
        explicit KeyManager(Profile *p, MainWindow* window = nullptr);
        ~KeyManager();

        void load();
        QList<PrimaPubKey *> getPubKeys() const;
        QList<PrimaSecKey *> getSecKeys() const;

    signals:
        void PubKeysLoaded();
        void SecKeysLoaded();
        void KeysLoaded();

    private slots:
        void loadSecretKeys();

    private:
        void gpgFinishedPublicKeys(int s, const QString& output);
        void gpgFinishedSecretKeys(int s, const QString& output);
        QDate strToDate(const QString& d) const;

        //QList<PrimaPubKey*> m_primaPubKeys;
        //QList<PrimaSecKey*> m_primaSecKeys;
        QHash<QString, PrimaPubKey*>* m_hashprimaPubKeys;
        QHash<QString, PrimaSecKey*>* m_hashprimaSecKeys;
        GPGManager* m_gpg;
};

#endif // KEYMANAGER_H
