#include <iostream>
#include <QSharedMemory>

#define MAX_INSTANCES_NB 10
#define PROFILE_OPTION "-p"
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
    }

    QSharedMemory shm(SHM_NAME);
    if (shm.attach(QSharedMemory::ReadOnly)) {
        // TODO : écrire dans un sémaphore pour lancer l'appli
    } else if (!shm.create(MAX_INSTANCES_NB * sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        exit(1);
    } else {
        // TODO : lancer un thread pour le lancement des fenêtres
    }
    return 0;
}
