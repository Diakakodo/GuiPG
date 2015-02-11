#include "guipgapp.h"
#include "../View/mainwindow.h"
#include <QDebug>

GuiPGApp::GuiPGApp(int& argc, char** argv)
    : QApplication(argc, argv) {

}

GuiPGApp::~GuiPGApp() {

}

void GuiPGApp::launchApp(int  profileId, Configuration* config) {
    MainWindow* w = new MainWindow(config->getProfileById(profileId), config);
    w->show();
}
