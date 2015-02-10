#include "profilemanager.h"

ProfileManager::ProfileManager(Configuration* cfg) : m_cfg(cfg) {

}

void ProfileManager::launch(Profile* p) {
    MainWindow* w = m_windows.value(p, new MainWindow(p, m_cfg));
    w->setFocus();
    m_windows.insert(p, w);
}
