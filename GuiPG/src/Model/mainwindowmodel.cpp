#include "mainwindowmodel.h"


MainWindowModel::MainWindowModel(GuiPGApp *app, Configuration* conf, unsigned profileId)
        : m_app(app), m_conf(conf) {

    m_profileId = profileId;
    //connect(this, &MainWindowModel::runApp2, m_app, &GuiPGApp::launchApp);
}

MainWindowModel::~MainWindowModel() {

}

void MainWindowModel::run() {
    QThread::sleep(200);
}

