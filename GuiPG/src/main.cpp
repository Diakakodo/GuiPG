#include <iostream>
#include <QObject>
#include <QSharedMemory>
#include <QSemaphore>
#include <QSystemSemaphore>
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
    /*
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
    */

    // TODO penser a tester le chargement de la configuration.
    Configuration config("config.xml");
    config.load();
    //QApplication app(argc, argv);

    // Instanciation du SHM
    QSharedMemory shm(SHM_NAME);
    if (false && shm.attach(QSharedMemory::ReadOnly)) {
        // Le SHM existe déja on écrit alors dedans.
        // TODO : écrire dans un sémaphore pour lancer l'appli
        qDebug() << "exist";
        shm.detach();
        exit(0);
    } else if (false && !shm.create(MAX_INSTANCES_NB * sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        exit(1);
    } else {
        // TODO : lancer un thread pour le lancement des fenêtres
        //QSemaphore sem(2);
        QSystemSemaphore sem(SYS_SEM_NAME, 0, QSystemSemaphore::Open);

        GuiPGApp app(argc, argv);
        //Test2 test2(&app, &sem);
        Launcher launcher(&app, &config, &sem);

        //QObject::connect(&launcher, &Launcher::runApp, &app, &GuiPGApp::launchApp);
        QObject::connect(&app, &GuiPGApp::lastWindowClosed, &launcher, &Launcher::stop);
        launcher.start();
        //launcher.listen();
        //qDebug() << "plop";
        if (!launcher.alreadyRun()) {
            app.exec();
        }
        launcher.wait();
        qDebug() << "fini";
        //return app.exec();
    }
    return 0;

}
