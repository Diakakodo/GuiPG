#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QThread>
#include <QSemaphore>
#include <QSharedMemory>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"

class Launcher : public QThread
{
        Q_OBJECT
    public:
        explicit Launcher(QSemaphore* sem, Configuration* conf, QSharedMemory* shm);

        ~Launcher();

        void run();

    signals:
        void runApp(Profile* p);

    private:
        QSemaphore* m_sem;
        Configuration* m_conf;
        QSharedMemory* m_shm;

};

#endif // LAUNCHER_H
