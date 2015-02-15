#include "guipgapp.h"
#include "../View/mainwindow.h"
#include <QDebug>

GuiPGApp::GuiPGApp(int& argc, char** argv)
    : QApplication(argc, argv) {

}

GuiPGApp::~GuiPGApp() {

}

void GuiPGApp::launchApp(Launcher* launcher, GuiPGApp* app, Configuration* config, unsigned profileId) {
    Profile* profile = config->getProfileById(profileId);
    MainWindowModel* model = new MainWindowModel(launcher, app, config, profile);
    MainWindow* w = new MainWindow(model);
    launcher->addMainWindow(profile, w);
    w->show();
}
