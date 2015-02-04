#include "launcher.h"
#include "../View/mainwindow.h"
#include <iostream>
#include <QDebug>

using namespace std;

Launcher::Launcher(GuiPGApp* app, Configuration* conf, int profileId)
    : m_app(app), m_conf(conf) {

    m_sem = new QSemaphore(1);
    m_shm = new QSharedMemory(SHM_NAME, this);
    m_profileId = profileId;
    m_launchers = QHash<Profile*, Launcher*>();
    m_stop = false;
    // TODO vérifier la compatibilité Windows/Unix pour le mode d'accés.
    m_systemSem = new QSystemSemaphore(SYS_SEM_NAME, 0, QSystemSemaphore::Create);
    QObject::connect(this, &Launcher::runApp, m_app, &GuiPGApp::launchApp);
}

Launcher::~Launcher() {
    // TODO libérer les ressources QHash and co ...
    //m_systemSem->acquire();
}

void Launcher::run() {
    if (m_profileId == -1) {
        // On est un gestionnaire de Launcher en fait ...
        listen();
    } else {
        // On est un vrai Launcher ...
        startInstance(m_conf->getProfileById(m_profileId));
    }
}

void Launcher::startInstance(Profile* p) {
    // On prend le mutex
    m_sem->acquire();
    unsigned* ids = (unsigned*) m_shm->data();
    unsigned id = 0;//ids[ids[0]];
    // On libère le mutex
    m_sem->release();
    // On emet le signal pour signifier a GuiPGApp de lancer la fenetre.
    emit runApp(m_conf->getProfileById(p->getId()), m_conf);
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
        unsigned idtmp = 1;
        m_shm->lock();
        unsigned* data = (unsigned*) m_shm->data();
        //memccpy(data, &idtmp, 1, sizeof(unsigned));
        *data = (unsigned) 0;
        m_shm->unlock();
        qDebug() << "temoin";

        // On notifie l'application principale qu'il y a des donénes a lire
        m_systemSem->release();
        // Et on quitte le thread.
        QThread::currentThread()->quit();
    } else if (!m_shm->create(sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        qDebug() << m_shm->errorString();
        QThread::currentThread()->quit();
    }
    // Le SHM est fraichement créée
    // On lance la première instance.
    Launcher* l = new Launcher(m_app, m_conf, 1);
    m_launchers.insert(m_conf->getProfileById(1), l);
    l->start();
    // On boucle avec une attente passive de données a lire sur le SHM.
    while (!m_stop) {
        m_systemSem->acquire();
        m_shm->lock();
        unsigned id = *((unsigned*) m_shm->data());
        m_shm->unlock();
        l = new Launcher(m_app, m_conf, id);
        m_launchers.insert(m_conf->getProfileById(id), l);
        l->start();
    }
}

