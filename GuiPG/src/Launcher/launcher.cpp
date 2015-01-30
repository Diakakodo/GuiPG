#include "launcher.h"

Launcher::Launcher(QSemaphore* sem, Configuration* conf)
    : m_sem(sem), m_conf(conf) {

}

Launcher::~Launcher() {

}

void Launcher::run() {
    m_sem->acquire();

}

