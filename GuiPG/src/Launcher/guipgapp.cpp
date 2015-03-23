#include "guipgapp.h"
#include "../View/mainwindow.h"
#include "../View/Profil/dialogprofile.h"

GuiPGApp::GuiPGApp(int& argc, char** argv)
    : QApplication(argc, argv) {
}

GuiPGApp::~GuiPGApp() {

}

Configuration* GuiPGApp::getConfig() const {
    return m_config;
}

void GuiPGApp::launchApp(Launcher* launcher, GuiPGApp* app, Configuration* config, unsigned profileId) {
    m_launcher = launcher;
    m_config = config;
    m_profileId = profileId;
    if (m_profileId == 0 || m_launcher->profileIsLoad(m_config->getProfileById(m_profileId))) {
        showDialogProfile();
        // Si aucun profile n'a était séléctionné, on notifie le launcher et on quitte.
        if (m_profileId == 0) {
            launcher->stop();
            return;
        }
    }

    if (m_profileId != 0) {
        Profile* profile = m_config->getProfileById(m_profileId);
        MainWindow* window = launcher->profileIsLoad(profile);
        if (window != nullptr) {
            window->raise();
        } else {
            MainWindowModel* model = new MainWindowModel(launcher, app, config, profile);
            MainWindow* w = new MainWindow(model);
            launcher->addMainWindow(profile, w);
            w->show();
        }
    }
}

void GuiPGApp::showDialogProfile() {
    DialogProfile d(m_config, m_launcher);
    QObject::connect(&d, &DialogProfile::selectProfile, this, &GuiPGApp::setProfileId);
    d.exec();
}

void GuiPGApp::setProfileId(unsigned profileId) {
    m_profileId = profileId;
}
