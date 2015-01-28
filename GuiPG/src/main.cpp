#include <iostream>
#include <QSharedMemory>

#define MAX_INSTANCES_NB 10
#define SHM_NAME "guipg"

using namespace std;

int main(int argc, char** argv) {
    QSharedMemory shm(SHM_NAME);
    if (shm.attach(QSharedMemory::ReadOnly)) {

    } else if (!shm.create(MAX_INSTANCES_NB * sizeof (unsigned))) {
        cerr << "Unable to init shared memory." << endl;
        exit(1);
    }
    return 0;
}
