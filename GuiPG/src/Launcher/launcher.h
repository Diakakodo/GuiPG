#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QThread>
#include <QSemaphore>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"
#include "guipgapp.h"
class GuiPGApp;
#include "../View/mainwindow.h"
class MainWindow;


class Launcher : public QThread {

    #define SHM_NAME     "guipg_shmkjebc"
    #define SYS_SEM_NAME "guipg_shm_sem"

        Q_OBJECT

    public:
        Launcher(GuiPGApp* app, Configuration* conf, int profileId = -1);

        ~Launcher();

        void run();

        void listen();

        bool alreadyRun();

        bool addMainWindow(Profile* p, MainWindow* window);

        MainWindow* profileIsLoad(Profile* p);

        void loadProfile(Profile* p, MainWindow* window);

        void UnloadProfileWithWindow(Profile* p);
        static QHash<Profile*, MainWindow*> m_profileMainWindowHash;

    signals:
        void runApp(Launcher* launcher, GuiPGApp* app, Configuration* conf, unsigned profileId);

    public slots:
        void stop();

    private:
        void startInstance(Profile* p);
        GuiPGApp* m_app;
        QSemaphore* m_sem;
        Configuration* m_conf;
        QSharedMemory* m_shm;
        int m_profileId;
        QSystemSemaphore* m_systemSem;
        bool m_stop;
};


#endif // LAUNCHER_H
