#include "launcher.h"
#include "../View/mainwindow.h"
#include <iostream>
#include <QDebug>
//*
using namespace std;
Launcher::Launcher(GuiPGApp* app, Configuration* conf, QSystemSemaphore* sem, int profileId)
    : m_app(app), m_conf(conf), m_systemSem(sem) {

    m_sem = new QSemaphore(1);
    m_shm = new QSharedMemory(SHM_NAME, this);
    m_profileId = profileId;
    m_launchers = QHash<Profile*, Launcher*>();
    m_stop = false;
    // Il faut garder le mode Open pour une compatibilité Windows/Unix
    // Si la semaphore existe elle est utilisée (et sa valeure est inchangée) sinon elle est
    // créée avec la valeure passée cette semaphore permet de controler les accés au SHM.
    ///m_systemSem = new QSystemSemaphore(SYS_SEM_NAME, 0, QSystemSemaphore::Open);
    QObject::connect(this, &Launcher::runApp, m_app, &GuiPGApp::launchApp);
}

Launcher::~Launcher() {
    // TODO libérer les ressources QHash and co ...
}

void Launcher::run() {
    //m_sem->acquire();
    //unsigned* ids = (unsigned*) m_shm->data();
    //unsigned id = 0;//ids[ids[0]];
    // On emet le signal pour signifier a GuiPGApp de lancer la fenetre.
    //emit runApp(m_conf->getProfileById(id));
    if (m_profileId == 0) {
        listen();
    } else {
        startInstance(m_conf->getProfileById(1));
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
    emit runApp(m_conf->getProfileById(p->getId()));
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

    if (alreadyRun()) {
        // Le SHM existe déja on écrit alors dedans.
        // TODO : écrire dans le SHM pour lancer l'appli

        // On notifie l'application principale qu'il y a des donénes a lire
        qDebug() << "exist";
        // Et on quitte le thread.
        pthread_exit(NULL);
        return; // Retour inutile mais bon.
    } else if (!m_shm.create(2 * sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        pthread_exit(NULL);
        exit(1);
    }
    // Le SHM est fraichement créée
    // On lance la première instance.
    Launcher* l = new Launcher(m_app, m_conf, m_systemSem, 1);
    m_launchers.insert(m_conf->getProfileById(1), l);
    l->start();
    //l->startInstance(m_conf->getProfileById(1));
    //Launcher* ll = new Launcher(m_app, m_conf, m_systemSem, 1);
    //ll->start();
    while (!m_stop) {
        m_systemSem->acquire();

    }
}

/*/

Test2::Test2(QApplication* app, QSemaphore* sem) : m_app(app), m_sem(sem) {

}

Test2::~Test2() {

}

void Test2::run() {
    m_sem->acquire();
    qDebug() << "plop";
    //emit runApp();
    //QApplication::sendEvent(m_app, new QEvent(QEvent::User));
}
//*/
