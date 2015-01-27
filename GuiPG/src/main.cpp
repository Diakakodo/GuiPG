#include "Configuration/configuration.h"
#include "Profile/profile.h"
#include "View/mainwindow.h"
#include <QDebug>
#include <QApplication>


int main(int argc, char** argv) {
    QApplication guiPg(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return guiPg.exec();

    /* CODE QUI DEVRAIT ETRE DANS UNE CLASSE DE TEST !!! */

    // Configuration cfg("../test.xml");
    // Profile p(1, "default");
    // cfg.load(&p);
    // cfg.setGPGExecutable("caca");
    // const QHash<QString, QDomElement>& vars = cfg.getVars();
    // for (QString k : vars.keys()) {
    //     qDebug() << k << " => " << vars.value(k).attribute("value");
    // }
    // cfg.save();
    // return 0;
}
