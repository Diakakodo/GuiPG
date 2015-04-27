#include "launcher.h"
#include "../View/mainwindow.h"
#include <iostream>

using namespace std;


QHash<Profile*, MainWindow*> Launcher::m_profileMainWindowHash = QHash<Profile*, MainWindow*>();
QSharedMemory* Launcher::SHM = nullptr;

/**
 * @brief Launcher::Launcher
 * @param app
 * @param conf
 * @param profileId Indique l'identifiant du profile a lancer
 */
Launcher::Launcher(GuiPGApp* app, Configuration* conf, int profileId)
    : m_app(app), m_conf(conf) {

    m_shm = new QSharedMemory(SHM_NAME, this);
    m_profileId = profileId;
    //m_profileMainWindowHash = QHash<Profile*, MainWindow*>();
    m_stop = false;
    // TODO vérifier la compatibilité Windows/Unix pour le mode d'accés.
    m_systemSem = new QSystemSemaphore(SYS_SEM_NAME, 0, QSystemSemaphore::Create);
    QObject::connect(this, &Launcher::runApp, m_app, &GuiPGApp::launchApp);
    if (m_profileId != 0) {
        QObject::connect(app, &GuiPGApp::lastWindowClosed, this, &Launcher::stop);
    }
    if (!Launcher::SHM) {
        Launcher::SHM = m_shm;
    }
}

Launcher::~Launcher() {
    // TODO libérer les ressources QHash and co ...
    delete m_shm;
    delete m_systemSem;
}

void Launcher::run() {
    listen();
}

bool Launcher::alreadyRun() {
    if (!m_shm->isAttached() && m_shm->attach()) {
        // Le SHM existait avant qu'on l'y attache...
        // on se détache
        m_shm->detach();
        return true;
    }
    return false;
}

void Launcher::stop() {
    // On notifie qu'il faut terminer.
    m_stop = true;
    // On débloque la boucle de lancemant (du listen).
    m_systemSem->release();
}


void Launcher::listen() {

    if (m_shm->attach(QSharedMemory::ReadWrite)) {
        // Le SHM existe déja on écrit alors dedans.
        m_shm->lock();
        unsigned* data = (unsigned*) m_shm->data();
        // On écris l'id du profile demandé.
        *data = (unsigned) m_profileId;
        m_shm->unlock();

        // On notifie l'application principale qu'il y a des donénes a lire
        m_systemSem->release();
        // Et on quitte le thread.
        pthread_exit(NULL);
    } else if (!m_shm->create(sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        pthread_exit(NULL);
    }
    // Le SHM est fraichement créée
    // On lance la première instance.
    emit runApp(this, m_app, m_conf, m_profileId);
    // On boucle avec une attente passive de données a lire sur le SHM.
    while (!m_stop) {
        m_systemSem->acquire();
        if (m_stop) {
            break;
        }
        m_shm->lock();
        unsigned id = *((unsigned*) m_shm->data());
        m_shm->unlock();
        emit runApp(this, m_app, m_conf, id);
    }
}

bool Launcher::addMainWindow(Profile* p, MainWindow* window) {
    if (p == nullptr || window == nullptr) {
        throw IllegalArgumentException("p == null || window == NULL");
    }
    if (profileIsLoad(p) != nullptr) {
        throw IllegalStateException("profileIsLoad(p) != nullptr");
    }

    // Si on a était lancé en attente de séléction de profile
    // alors on vient de récupérer le profile séléctionné, on peut se brancher au signal.
    if (m_profileId == 0) {
        QObject::connect(m_app, &GuiPGApp::lastWindowClosed, this, &Launcher::stop);
    }
    m_profileId = p->getId();
    m_profileMainWindowHash.insert(p, window);
    return true;
}

MainWindow* Launcher::profileIsLoad(Profile* p) {
    if (p == nullptr) {
        throw IllegalArgumentException("p == null");
    }
    if (m_profileMainWindowHash.contains(p)) {
        return m_profileMainWindowHash.value(p);
    }
    return NULL;
}

void Launcher::loadProfile(Profile* p, MainWindow* window) {
    Profile* key = m_profileMainWindowHash.key(window);
    m_profileMainWindowHash.remove(key);
    addMainWindow(p, window);
}

void Launcher::UnloadProfileWithWindow(Profile* p) {
    m_profileMainWindowHash.remove(p);
}
