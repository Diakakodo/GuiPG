#include "mainwindowmodel.h"
#include <QDebug>


MainWindowModel::MainWindowModel(Launcher* launcher, GuiPGApp *app, Configuration* conf, Profile* profile)
        : m_launcher(launcher), m_app(app), m_conf(conf), m_profile(profile) {
}

MainWindowModel::~MainWindowModel() {

}

Launcher* MainWindowModel::getLauncher() const {
    return m_launcher;
}

GuiPGApp* MainWindowModel::getGuiPGApp() const {
    return m_app;
}

Configuration* MainWindowModel::getConf() const {
    return m_conf;
}

Profile* MainWindowModel::getProfile() const {
    return m_profile;
}

void MainWindowModel::loadProfile(unsigned profileId, MainWindow* window) {
    Profile* p = m_conf->getProfileById(profileId);
    MainWindow* w = m_launcher->profileIsLoad(p);
    if (w != nullptr) {
        w->raise();
    } else {
        m_launcher->loadProfile(p, window);
        m_profile = p;
    }
}

