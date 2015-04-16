#include "profilemanager.h"

ProfileManager::ProfileManager(Configuration* cfg) : m_cfg(cfg) {

}

void ProfileManager::launch(Profile* p) {
    if (p == nullptr) {
        // not used. La classe entière est inutile. TODO delette tout ca.
    }
    //MainWindow* w = m_windows.value(p, new MainWindow(p, m_cfg));
    //w->setFocus();
    //m_windows.insert(p, w);
}
