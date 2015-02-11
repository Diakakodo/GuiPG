#include "launcher.h"
#include "../View/mainwindow.h"
#include <iostream>
#include <QDebug>

using namespace std;

Launcher::Launcher(GuiPGApp* app, Configuration* conf, int profileId)
    : m_app(app), m_conf(conf) {

    m_shm = new QSharedMemory(SHM_NAME, this);
    m_profileId = profileId;
    m_launchers = QHash<Profile*, Launcher*>();
    m_stop = false;
    MainWindowModel m(app,conf, profileId);
    // TODO vérifier la compatibilité Windows/Unix pour le mode d'accés.
    m_systemSem = new QSystemSemaphore(SYS_SEM_NAME, 0, QSystemSemaphore::Create);
    QObject::connect(this, &Launcher::runApp, m_app, &GuiPGApp::launchApp);
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
        // TODO : écrire dans le SHM pour lancer l'appli
        qDebug() << "exist";
        m_shm->lock();
        unsigned* data = (unsigned*) m_shm->data();
        //memccpy(data, &idtmp, 1, sizeof(unsigned));
        *data = (unsigned) 0;
        m_shm->unlock();
        qDebug() << "temoin";

        // On notifie l'application principale qu'il y a des donénes a lire
        m_systemSem->release();
        // Et on quitte le thread.
        pthread_exit(NULL);
    } else if (!m_shm->create(sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        qDebug() << m_shm->errorString();
        pthread_exit(NULL);
    }
    // Le SHM est fraichement créée
    // On lance la première instance.
    emit runApp(1, m_conf);
    // On boucle avec une attente passive de données a lire sur le SHM.
    while (!m_stop) {
        m_systemSem->acquire();
        if (m_stop) {
            break;
        }
        m_shm->lock();
        unsigned id = *((unsigned*) m_shm->data());
        m_shm->unlock();
        qDebug() << id;
        if (id == 0) {
            // TODO lancer avec l'option -p.
            id = 0;
        }
        emit runApp(id, m_conf);
    }
}

