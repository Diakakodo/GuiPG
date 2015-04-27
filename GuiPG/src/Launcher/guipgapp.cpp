#include "guipgapp.h"
#include "../View/mainwindow.h"
#include "../View/Profil/dialogprofile.h"
#include "../View/GpgItems/gpgitem.h"

GuiPGApp::GuiPGApp(int& argc, char** argv)
    : QApplication(argc, argv) {
    setStyleSheet("QTreeView { show-decoration-selected: 1; }"
                  "QTreeView::Widget:hover {"
                       "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
                       "border: 1px solid #bfcde4;"
                   "}");
    setStyleSheet(
                "QTreeView {"
                    "alternate-background-color: #F2F2F2;"
                "}"
    );
    setStyleSheet(
                "QTreeView { show-decoration-selected: 1; }"
                "QTreeView::Widget:hover {"
                     "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
                     "border: 1px solid #bfcde4;"
                 "}"
                "QTreeView::branch:has-siblings:!adjoins-item {"
                     "border-image: url(:/icones/res/Icones/Tree/vline.png) 0;"
                 "}"

                 "QTreeView::branch:has-siblings:adjoins-item {"
                     "border-image: url(:/icones/res/Icones/Tree/branch-more.png) 0;"
                 "}"

                 "QTreeView::branch:!has-children:!has-siblings:adjoins-item {"
                     "border-image: url(:/icones/res/Icones/Tree/branch-end.png) 0;"
                 "}"

                 "QTreeView::branch:has-children:!has-siblings:closed,"
                 "QTreeView::branch:closed:has-children:has-siblings {"
                         "border-image: none;"
                         "image: url(:/icones/res/Icones/Tree/branch-closed.png);"
                 "}"

                 "QTreeView::branch:open:has-children:!has-siblings,"
                 "QTreeView::branch:open:has-children:has-siblings  {"
                         "border-image: none;"
                         "image: url(:/icones/res/Icones/Tree/branch-open.png);"
                 "}"
    );
}

GuiPGApp::~GuiPGApp() {

    if (m_config) {
        delete m_config;
    }
    if (m_launcher) {
        delete m_launcher;
    }

}

Configuration* GuiPGApp::getConfig() const {
    return m_config;
}

void GuiPGApp::launchApp(Launcher* launcher, GuiPGApp* app, Configuration* config, unsigned profileId) {
    m_launcher = launcher;
    m_config = config;
    m_profileId = profileId;
    if (m_profileId == 0 || m_launcher->profileIsLoad(m_config->getProfileById(m_profileId))) {
        showDialogProfile();
        // Si aucun profile n'a était séléctionné, on notifie le launcher et on quitte.
        if (m_profileId == 0) {
            launcher->stop();
            return;
        }
    }

    if (m_profileId != 0) {
        Profile* profile = m_config->getProfileById(m_profileId);
        MainWindow* window = launcher->profileIsLoad(profile);
        if (window != nullptr) {
            app->setActiveWindow(window);
            window->raise();
        } else {
            MainWindowModel* model = new MainWindowModel(launcher, app, config, profile);
            MainWindow* w = new MainWindow(model);
            launcher->addMainWindow(profile, w);
            w->show();
        }
    }
}

void GuiPGApp::showDialogProfile() {
    DialogProfile d(m_config, m_launcher);
    QObject::connect(&d, &DialogProfile::selectProfile, this, &GuiPGApp::setProfileId);
    d.exec();
}

void GuiPGApp::setProfileId(unsigned profileId) {
    m_profileId = profileId;
}
