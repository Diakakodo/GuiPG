#include <iostream>
#include <QObject>
#include <QStandardPaths>
#include "Tests/testmanager.h"
#include "QApplication"
#include "Profile/profile.h"
#include "View/mainwindow.h"
#include "View/keycreation.h"
#include "Launcher/guipgapp.h"
#include "Configuration/configuration.h"
#include "Launcher/launcher.h"

#define MAX_INSTANCES_NB 10
#define PROFILE_OPTION "-P"
#define TEST_OPTION "-t"

#ifndef _WIN32
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#endif // _WIN32
using namespace std;


bool hasProfileOpt(int argc, char** argv) {
    int i = 0;
    while (i < argc && *argv) {
        if (strncmp(*argv, PROFILE_OPTION, strlen(PROFILE_OPTION) + 1) == 0) {
            return true;
        }
        ++i;
        ++argv;
    }
    return false;
}

#ifndef _WIN32
void gestionnaire(int signum) {
    QSharedMemory* shm = Launcher::SHM;
    switch (signum) {
    case SIGSEGV:
    case SIGINT:
    case SIGTERM:
        shm->detach();
        shm->destroyed();
        exit(EXIT_FAILURE);
        break;
    default:
        fprintf(stderr, "Signal non géré recu. (%d)\n", 2);
    }
}

void buildHandler() {
    // On construit notre action
    struct sigaction action;
    action.sa_handler = gestionnaire;
    action.sa_flags = 0;
    if (sigfillset(&action.sa_mask) == -1) {
      perror("sigfilltset");
      exit(EXIT_FAILURE);
    }

    // On associe l'action à SIGINT
    if (sigaction(SIGINT, &action, NULL) == -1) {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }
    // On associe l'action à SIGTERM
    if (sigaction(SIGTERM, &action, NULL) == -1) {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }
    // On associe l'action à SIGSEGV
    if (sigaction(SIGSEGV, &action, NULL) == -1) {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }
}
#endif

int main(int argc, char** argv) {

    // Flag permettant de savoir si l'option PROFILE_OPTION est présente en argument.
    bool dashP = hasProfileOpt(argc, argv);

    GuiPGApp app(argc, argv);
    Configuration config(QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0] + "/.guipgconf.xml");
    if (!config.load()) {
        if (!config.save()) {
            fprintf(stderr, "Impossible de créer le fichier de configuration.");
            return EXIT_FAILURE;
        }
        if (!config.load()) {
            fprintf(stderr, "Impossible de charger le fichier de configuration.");
            return EXIT_FAILURE;
        }
    }
    Launcher launcher(&app, &config, (dashP ? 0 : config.getDefaultProfileId()));
#ifndef _WIN32
    buildHandler();
#endif

    launcher.start();
    if (!launcher.alreadyRun()) {
        try {
            app.exec();
        } catch (QException& e) {
            launcher.stop();
        }

        config.save();
    }
    launcher.wait();
    return EXIT_SUCCESS;
}
