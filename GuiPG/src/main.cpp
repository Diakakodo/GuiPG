#include <iostream>
#include <QObject>
#include "Tests/testmanager.h"
#include "QApplication"
#include "Profile/profile.h"
#include "View/mainwindow.h"
#include "Launcher/guipgapp.h"
#include "Configuration/configuration.h"
#include "Launcher/launcher.h"


#include <QDebug>

#define MAX_INSTANCES_NB 10
#define PROFILE_OPTION "-p"
#define TEST_OPTION "-t"
//#define SHM_NAME "guipg"

using namespace std;

int main(int argc, char** argv) {

    unsigned id = 0;
    ++argv;
    while (*argv != NULL) {
        if (strcmp(*argv, PROFILE_OPTION) == 0) {
            ++*argv;
            if (*argv == NULL) {
                cerr << "Missing argument after '" PROFILE_OPTION "'" << endl;
                exit(1);
            } else {
                QString a(*argv);
                bool ok = false;
                id = a.toUInt(&ok);
                if (!ok) {
                    cerr << "Invalid profile id" << endl;
                    exit(1);
                }
            }
        }
        if (strcmp(*argv, TEST_OPTION) == 0) {
            TestManager tmanager;
            tmanager.runTests();
            ++*argv;
            exit(0);
        }
    }


    // TODO penser a tester le chargement de la configuration.
    Configuration config("config.xml");
    config.load();

    GuiPGApp app(argc, argv);
    Launcher launcher(&app, &config);
    QObject::connect(&app, &GuiPGApp::lastWindowClosed, &launcher, &Launcher::stop);
    launcher.start();
    if (!launcher.alreadyRun()) {
        app.exec();
    }
    launcher.wait();
    return EXIT_SUCCESS;
}
