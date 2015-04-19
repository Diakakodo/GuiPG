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

        QList<PrimaPubKey *> getPubKeys() const;
        QList<PrimaSecKey *> getSecKeys() const;
        MainWindow* getMainWindow();
        void setMainWindow(MainWindow* window);

    public slots:
        void load();

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
        QHash<QString, SubPubKey*>* m_hashsubPubKeys;
        QHash<QString, SubSecKey*>* m_hashsubSecKeys;
        GPGManager* m_gpg;
        MainWindow* m_window;
};

#endif // KEYMANAGER_H
