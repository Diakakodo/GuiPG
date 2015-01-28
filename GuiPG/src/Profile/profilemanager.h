#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>
#include "../Configuration/configuration.h"
#include "../View/mainwindow.h"

class ProfileManager : public QObject {
    Q_OBJECT

    public:
        explicit ProfileManager(Configuration* cfg);

        /**
         * @brief launch Lance un profil.
         * @param p Le profil à lancer.
         */
        void launch(Profile* p);

    private:
        Configuration* m_cfg;
        QHash<Profile*, MainWindow*> m_windows;
};

#endif // PROFILEMANAGER_H
