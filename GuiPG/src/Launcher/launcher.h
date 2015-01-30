#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QThread>
#include <QSemaphore>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"

class Launcher : public QThread
{
    public:
        explicit Launcher(QSemaphore* sem, Configuration* conf);

        ~Launcher();

        void run();

    signals:
        void runApp(Profile* p);

    private:
        QSemaphore* m_sem;
        Configuration* m_conf;

};

#endif // LAUNCHER_H
