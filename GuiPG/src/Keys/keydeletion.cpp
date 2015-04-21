#include "keydeletion.h"
#include "../GPG/action.h"


KeyDeletion::KeyDeletion(KeyManager* keyManager, Profile* profile, QString keyId) :
    QObject(),
    m_profile(profile),
    m_keyManager(keyManager),
    m_keyId(keyId)
{

}

KeyDeletion::~KeyDeletion()
{
}

GPGManager* buildSecreteKeysDeleteGpg(Profile* profile, QString keyId) {
    QStringList interactions;
    interactions << "y";
    interactions << "y";
    Action keyDeletion(QString("--delete-secret-keys"), QStringList(keyId), QStringList("--command-fd=0") << "--status-fd=1", interactions);
    GPGManager* gpg = new GPGManager(profile);
    gpg->setAction(keyDeletion);
    return gpg;
}

void KeyDeletion::deleteKeys() {
    GPGManager* gpg = buildSecreteKeysDeleteGpg(m_profile, m_keyId);
    connect(gpg, &GPGManager::finished, this, &KeyDeletion::onPrivateDeletionToPublicDeletion);
    gpg->execute();
}

void KeyDeletion::onPrivateDeletionToPublicDeletion() {
    deletePublicKey();
}

void KeyDeletion::deletePublicKey() {
    QStringList interactions;
    interactions << "y";
    Action keyDeletion(QString("--delete-keys"), QStringList(m_keyId), QStringList("--command-fd=0") << "--status-fd=1", interactions);
    GPGManager* gpg = new GPGManager(m_profile);
    gpg->setAction(keyDeletion);
    connect(gpg, &GPGManager::finished, this, &KeyDeletion::onDeletionCompleted);
    gpg->execute();
}

void KeyDeletion::deleteSecretKey() {
    GPGManager* gpg = buildSecreteKeysDeleteGpg(m_profile, m_keyId);
    connect(gpg, &GPGManager::finished, this, &KeyDeletion::onDeletionCompleted);
    gpg->execute();
}

void KeyDeletion::onDeletionCompleted() {
    m_keyManager->load();
}
