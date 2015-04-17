#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>
#include "../Configuration/configuration.h"
#include "../Launcher/guipgapp.h"
class GuiPGApp;
#include "../Launcher/launcher.h"
class Launcher;
#include "../View/mainwindow.h"
class MainWindow;
#include "../Keys/keymanager.h"

class MainWindowModel : public QObject {

        Q_OBJECT

    public:
        MainWindowModel(Launcher* launcher, GuiPGApp* app, Configuration* conf, Profile* profile = NULL);
        ~MainWindowModel();
        Launcher* getLauncher() const;
        GuiPGApp* getGuiPGApp() const;
        Configuration* getConf() const;
        Profile* getProfile() const;
        void loadProfile(unsigned profileId, MainWindow* window);
        KeyManager* getKeyManager() const;
        void initKeyManager(MainWindow *window = nullptr);

    signals:
        void keysChanged();

    public slots:
        void emitKeysChanged();

    private:
        Launcher* m_launcher;
        GuiPGApp* m_app;
        Configuration* m_conf;
        Profile* m_profile;
        KeyManager* m_keyManager;
};


#endif // MAINWINDOWMODEL_H
