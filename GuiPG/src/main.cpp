#include "Configuration/configuration.h"
#include "Profile/profile.h"
#include <QDebug>

int main(void) {
    Configuration cfg("test.xml");
    Profile p(1, "default");
    cfg.load(&p);
    const QHash<QString, QString>& vars = cfg.getVars();
    for (QString k : vars.keys()) {
        qDebug() << k << " => " << vars.value(k);
    }
    return 0;
}
