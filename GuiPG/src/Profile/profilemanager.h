#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>
#include "../Configuration/configuration.h"

class ProfileManager : public QObject {
    Q_OBJECT

    public:
        explicit ProfileManager(Configuration* cfg);

    private:
        Configuration* m_cfg;
};

#endif // PROFILEMANAGER_H
