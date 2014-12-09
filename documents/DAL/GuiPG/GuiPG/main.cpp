//#include "launcher.h"
//#include "instance.h"
#include <cstdlib>
#include <QApplication>
#include <QDebug>
#include <unistd.h>
#include "maquette.h"


int main(int argc, char** argv) {

    QApplication coquille(argc, argv);

    Maquette m;
    m.show();

    return coquille.exec();
}

