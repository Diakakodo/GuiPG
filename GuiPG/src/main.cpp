#include "Configuration/configuration.h"
#include "Profile/profile.h"
#include <QDebug>

int main(void) {
    Configuration cfg("../test.xml");
    Profile p(1, "default");
    cfg.load(&p);
    cfg.setGPGExecutable("caca");
    const QHash<QString, QDomElement>& vars = cfg.getVars();
    for (QString k : vars.keys()) {
        qDebug() << k << " => " << vars.value(k).attribute("value");
    }
    cfg.save();
    return 0;
}
