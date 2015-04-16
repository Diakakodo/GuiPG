#ifndef GUIPGAPP_H
#define GUIPGAPP_H

#include <QObject>
#include <QApplication>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"
#include "launcher.h"
class Launcher;
#include "../Model/mainwindowmodel.h"
class MainWindowModel;

class GuiPGApp : public QApplication {

        Q_OBJECT

    public:
        GuiPGApp(int& argc, char** argv);
        Configuration* getConfig() const;

        ~GuiPGApp();
    signals:
    public slots:
        void launchApp(Launcher* launcher, GuiPGApp* app, Configuration* conf, unsigned profileId);

    private:
        Configuration* m_config;
        Launcher* m_launcher;
        unsigned m_profileId;

    private slots:
        void showDialogProfile();
        void setProfileId(unsigned profileId);
};

#endif // GUIPGAPP_H
