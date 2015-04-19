#include "keydeletion.h"
#include "../GPG/action.h"


KeyDeletion::KeyDeletion(MainWindow*parent) :
    QDialog(parent),
    m_window(parent),
    m_profile(parent->getProfil()),
    m_manager(new GPGManager(m_profile))
{

}

KeyDeletion::~KeyDeletion()
{
    delete m_manager;
}



void KeyDeletion::deletePublicKey(QString keyId) {
    QStringList interactions;
    interactions << "o";
    Action keyDeletion(QString("--delete-keys"), QStringList(keyId), QStringList(), interactions);
    m_manager->setAction(keyDeletion);
    connect(m_manager, &GPGManager::finished, this, &KeyDeletion::onDeletionCompleted);
    m_manager->execute();
}

void KeyDeletion::deleteSecretKey(QString keyId) {
    QStringList interactions;
    interactions << "o";
    interactions << "o";
    Action keyDeletion(QString("--delete-secret-keys"), QStringList(keyId), QStringList(), interactions);
    m_manager->setAction(keyDeletion);
    connect(m_manager, &GPGManager::finished, this, &KeyDeletion::onDeletionCompleted);
    m_manager->execute();
}

void KeyDeletion::onDeletionCompleted() {
    m_window->refreshKeys();
}
