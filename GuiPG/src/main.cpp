#include <iostream>
#include <QObject>
#include <QSharedMemory>
#include <QSemaphore>
#include "Tests/testmanager.h"
#include "QApplication"
#include "Profile/profile.h"
#include "View/mainwindow.h"
#include "Launcher/guipgapp.h"
#include "Configuration/configuration.h"
#include "Launcher/launcher.h"

#define MAX_INSTANCES_NB 10
#define PROFILE_OPTION "-p"
#define TEST_OPTION "-t"
#define SHM_NAME "guipg"

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
        }
    }

    // TODO penser a tester le chargement de la configuration.
    Configuration config("config.xml");
    config.load();



    QSharedMemory shm(SHM_NAME);
    if (shm.attach(QSharedMemory::ReadOnly)) {
        // TODO : écrire dans un sémaphore pour lancer l'appli
        exit(0);
    } else if (!shm.create(MAX_INSTANCES_NB * sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        exit(1);
    } else {
        // TODO : lancer un thread pour le lancement des fenêtres

        QSemaphore sem(0);

        GuiPGApp app(argc, argv);
        Launcher launcher(&sem, &config, &shm);

        QObject::connect(&launcher, &Launcher::runApp, &app, &GuiPGApp::launchApp);

        launcher.start();

        return app.exec();
    }
    return 0;
}
