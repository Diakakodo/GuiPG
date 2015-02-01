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
//*

class Launcher : public QThread {

    #define SHM_NAME     "guipg_shm0"
    #define SYS_SEM_NAME "guipg_shm_sem"

        Q_OBJECT

    public:
        Launcher(GuiPGApp* app, Configuration* conf, QSystemSemaphore* sem, int profileId = 0);

        ~Launcher();

        void run();

        void listen();

        bool alreadyRun();

    signals:
        void runApp(Profile* p);

    public slots:
        void stop();

    private:
        void startInstance(Profile* p);
        GuiPGApp* m_app;
        QSemaphore* m_sem;
        Configuration* m_conf;
        QSharedMemory* m_shm;
        QHash<Profile*, Launcher*> m_launchers;
        int m_profileId;
        QSystemSemaphore* m_systemSem;
        bool m_stop;
};
/*/
#include <QApplication>
#include <QDebug>

class Test2 : public QThread {
    //Q_OBJECT
    public:
        explicit Test2(QApplication* app, QSemaphore* sem);// : m_app(app), m_sem(sem) {
        ~Test2();
        //}
        void run();
    signals:
        void runApp();
    private:
        QApplication* m_app;
        QSemaphore* m_sem;
};
//*/



#endif // LAUNCHER_H
