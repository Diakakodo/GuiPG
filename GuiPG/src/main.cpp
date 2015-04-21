#include <iostream>
#include <QObject>
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
//#define SHM_NAME "guipg"

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

int main(int argc, char** argv) {
    // Flag permettant de savoir si l'option PROFILE_OPTION est présente en argument.
    bool dashP = hasProfileOpt(argc, argv);

    // TODO penser a tester le chargement de la configuration.
    Configuration config(QCoreApplication::applicationDirPath() + "../config.xml");
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
    GuiPGApp app(argc, argv);
    Launcher launcher(&app, &config, (dashP ? 0 : config.getDefaultProfileId()));
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
