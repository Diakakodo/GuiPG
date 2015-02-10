#include "guipgapp.h"
#include "../View/mainwindow.h"
#include <QDebug>

GuiPGApp::GuiPGApp(int& argc, char** argv)
    : QApplication(argc, argv) {

}

GuiPGApp::~GuiPGApp() {

}

void GuiPGApp::launchApp(Profile* p, Configuration* config) {
    qDebug() << p->getName();
    MainWindow* w = new MainWindow(p, config);
    w->show();
}
