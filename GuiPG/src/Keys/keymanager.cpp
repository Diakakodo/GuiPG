#include "keymanager.h"

KeyManager::KeyManager(const Profile *p) : m_gpg(new GPGManager(p)) {

}

KeyManager::~KeyManager() {
    qDeleteAll(m_keys);
    delete m_gpg;
}
