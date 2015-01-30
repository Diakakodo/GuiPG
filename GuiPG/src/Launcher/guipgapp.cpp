#include "guipgapp.h"
#include "../View/mainwindow.h"

GuiPGApp::GuiPGApp(int& argc, char** argv)
    : QApplication(argc, argv) {

}

GuiPGApp::~GuiPGApp() {

}

void GuiPGApp::launchApp(Profile* p) {
    MainWindow* w = new MainWindow(p);
    w->show();
}
