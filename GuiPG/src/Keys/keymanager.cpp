#include "keymanager.h"

KeyManager::KeyManager(const Profile *p) : m_gpg(new GPGManager(p)) {
    connect(m_gpg, &GPGManager::finished, this, &KeyManager::gpgFinished);
}

KeyManager::~KeyManager() {
    qDeleteAll(m_keys);
    delete m_gpg;
}

void KeyManager::load() {
    Action a("--list-keys");
    m_gpg->setAction(a);
}

void KeyManager::gpgFinished(int s, const QString &output) {

}
