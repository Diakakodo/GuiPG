#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>
#include "../Configuration/configuration.h"
#include "../Launcher/guipgapp.h"
class GuiPGApp;
#include "../Launcher/launcher.h"
class Launcher;

class MainWindowModel : public QObject {

        Q_OBJECT

    public:
        MainWindowModel(Launcher* launcher, GuiPGApp* app, Configuration* conf, Profile* profile = NULL);
        ~MainWindowModel();
        Launcher* getLauncher() const;
        GuiPGApp* getGuiPGApp() const;
        Configuration* getConf() const;
        Profile* getProfile() const;
        void loadProfile(unsigned profileId);

    private:
        Launcher* m_launcher;
        GuiPGApp* m_app;
        Configuration* m_conf;
        Profile* m_profile;
};


#endif // MAINWINDOWMODEL_H
