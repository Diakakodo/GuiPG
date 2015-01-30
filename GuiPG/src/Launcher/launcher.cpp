#include "launcher.h"
#include "../View/mainwindow.h"

Launcher::Launcher(QSemaphore* sem, Configuration* conf, QSharedMemory* shm)
    : m_sem(sem), m_conf(conf), m_shm(shm) {

}

Launcher::~Launcher() {

}

void Launcher::run() {
    m_sem->acquire();
    unsigned* ids = (unsigned*) m_shm->data();
    unsigned id = ids[ids[0]];
    MainWindow* window = new MainWindow(m_conf->getProfileById(id));
    window->show();
}

