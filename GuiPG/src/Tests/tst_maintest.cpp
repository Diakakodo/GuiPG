#include <QString>
#include <QtTest>
#include "../Profile/profile.h"
#include "../Profile/profilemanager.h"
#include "../Configuration/configuration.h"
#include "../GPG/action.h"
#include "../Model/mainwindowmodel.h"
#include "../View/mainwindow.h"
#include "../View/keyexport.h"
#include "../View/Profil/profilecreation.h"
#include "../Launcher/launcher.h"
#include "../GPG/gpgmanager.h"
#include "stdlib.h"
#include <stdio.h>
#include "unistd.h"
#include "QEventLoop"
#include "QDebug"

class MainTest : public QObject
{
    Q_OBJECT

public:
    MainTest();

private:
    Configuration* m_config;
    GuiPGApp* m_app;

private Q_SLOTS:
    void testCase_u3();
    void testCase_u5();
    void testCase_u6();
    void testCase_u7();
    void testCase_u8();
    void testCase_u10();
    void testCase_nr1();
    void testCase_nr2();
    void testLoadConfig();

};

MainTest::MainTest()
{
    Configuration* config = new Configuration("../config.xml");
    config->load();
    m_config = config;
    int argc = 1;
    char* argv[] = {"~/projet_pgp/GuiPG/build/GuiPG"};
    GuiPGApp* app = new GuiPGApp(argc, argv);
    m_app = app;
}

void MainTest::testCase_u3()
{
    QList<Profile*> profiles = m_config->getProfiles();
    m_config->addProfile(new Profile(1751, "test"));
    QVERIFY(profiles.length() == m_config->getProfiles().length() - 1);
    QVERIFY(m_config->getProfileById(1751) != nullptr);
    m_config->deleteProfile(1751);
    QVERIFY(m_config->getProfileById(1751) == nullptr);
    QVERIFY(profiles == m_config->getProfiles());
}

void MainTest::testCase_u5()
{
    Profile p(66, "Mister T");
    p.setConfigurationPath("/");
    QString s = p.getConfigurationPath();
    QVERIFY(p.getConfigurationPath() == "/");
    p.setGPGExecutable("/");
    QVERIFY(p.getGPGExecutable() == "/");
    QVERIFY(p.getId() == 66);
    QVERIFY(p.getName() == "Mister T");
}

void MainTest::testCase_u6()
{
    Launcher launcher(m_app, m_config);
    //QVERIFY(launcher.alreadyRun() == false);
    MainWindowModel model(&launcher, m_app, m_config, m_config->getDefaultProfile());
    MainWindow mainWindow(&model);
    //QVERIFY_EXCEPTION_THROWN(launcher.addMainWindow(NULL, &mainWindow), IllegalArgumentException);
    //QVERIFY_EXCEPTION_THROWN(launcher.addMainWindow(m_config->getDefaultProfile(), NULL), IllegalArgumentException);
    launcher.addMainWindow(m_config->getDefaultProfile(), &mainWindow);
    launcher.start();
    //QVERIFY(launcher.alreadyRun() == true);
    QVERIFY(launcher.profileIsLoad(m_config->getDefaultProfile()) != NULL);
    launcher.UnloadProfileWithWindow(m_config->getDefaultProfile());
    launcher.stop();
    while(launcher.isRunning());
    //QVERIFY(launcher.alreadyRun() == true);
}

void MainTest::testCase_u7()
{
    QStringList interactions = (QStringList() << "1" << "2" << "3");
    Action a("test", QStringList(), QStringList(), interactions);
    QVERIFY(a.getCmd() == "test");
    QVERIFY(a.getArgs() == QStringList());
    QVERIFY(a.getOptions() == QStringList());
    QVERIFY(a.getInteractions() == (QStringList() << "1\n" << "2\n" << "3\n"));
    QVERIFY(a.nextInteraction() == "1\n");
    QVERIFY(a.nextInteraction() == "2\n");
    QVERIFY(a.nextInteraction() == "3\n");
    //Vérifier que a.nextInteraction() lance une exception (qt 5.3 requis)
    //QVERIFY_EXCEPTION_THROWN(a.nextInteraction(), IllegalStateException);
}

void MainTest::testCase_u8()
{
    GPGManager manager(m_config->getDefaultProfile());
    Action a("--version", QStringList(), QStringList());
    manager.setAction(a);
    manager.execute();
    QVERIFY(manager.getOutput() != "");
}

void MainTest::testCase_u10()
{
    Launcher launcher(m_app, m_config, m_config->getDefaultProfileId());
    MainWindowModel model(&launcher, m_app, m_config, m_config->getDefaultProfile());
    QVERIFY(model.getLauncher() == &launcher);
    QVERIFY(model.getGuiPGApp() == m_app);
    QVERIFY(model.getConf() == m_config);
    QVERIFY(model.getProfile() == m_config->getDefaultProfile());
    MainWindow mainWindow(&model);
    model.loadProfile(m_config->getDefaultProfileId(), &mainWindow);
    model.initKeyManager();
    QVERIFY(model.getKeyManager() != NULL);
}

void MainTest::testCase_nr1()
{
    remove("/tmp/TEST");


    Launcher launcher(m_app, m_config, m_config->getDefaultProfileId());
    MainWindowModel model(&launcher, m_app, m_config, m_config->getDefaultProfile());
    MainWindow mainWindow(&model);
    KeyExport* keyExport = new KeyExport(&mainWindow);
    keyExport->exportFunction(KeyExport::FILE, "", "/tmp/TEST");
    QVERIFY(remove("/tmp/TEST") != -1);
}

void MainTest::testCase_nr2()
{

    Launcher launcher(m_app, m_config, m_config->getDefaultProfileId());
    MainWindowModel model(&launcher, m_app, m_config, m_config->getDefaultProfile());
    MainWindow mainWindow(&model);
    Profile* p = new Profile(1234, "test");
    p->setConfigurationPath("/tmp");
    p->setGPGExecutable("/usr/bin/gpg");
    m_config->addProfile(p);
    for (int i=0; i < 20; i++) {
        mainWindow.changeProfil(1);
        mainWindow.changeProfil(1234);
    }
    m_config->deleteProfile(p->getId());
}

void MainTest::testLoadConfig()
{
    Configuration config("../config.xml");
    QVERIFY(config.load() == true);
}

QTEST_MAIN(MainTest)

#include "tst_maintest.moc"
