#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>
#include <QThread>
#include <QSemaphore>
#include "../Configuration/configuration.h"
#include "../Launcher/guipgapp.h"

class MainWindowModel : public QThread {

        Q_OBJECT

    public:
        MainWindowModel(GuiPGApp* app, Configuration* conf, unsigned profileId = 0);
        ~MainWindowModel();
        void run();
    signals:
        void runApp2(Profile* p, Configuration* config);

    private:
        GuiPGApp* m_app;
        QSemaphore* m_sem;
        Configuration* m_conf;
        unsigned m_profileId;
        //QSystemSemaphore* m_systemSem;
};


#endif // MAINWINDOWMODEL_H
