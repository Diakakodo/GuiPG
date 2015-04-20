#ifndef KEYDELETION_H
#define KEYDELETION_H

#include <QObject>
#include "../Profile/profile.h"
#include "../View/mainwindow.h"

class KeyDeletion : public QObject
{
    Q_OBJECT

public:

    explicit KeyDeletion(KeyManager* keyManager, Profile* profile, QString keyId);
    ~KeyDeletion();
    void deletePublicKey();
    void deleteSecretKey();
    void deleteKeys();

private slots:
    void onPrivateDeletionToPublicDeletion();

private:
    void onDeletionCompleted();
    Profile* m_profile;
    KeyManager* m_keyManager;
    QString m_keyId = "";
};


#endif // KEYDELETION_H
