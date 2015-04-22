#include <QString>
#include <QtTest>
#include "../Profile/profile.h"
#include "../Profile/profilemanager.h"
#include "../Configuration/configuration.h"
#include "../GPG/action.h"
#include "../Model/mainwindowmodel.h"
#include "../View/mainwindow.h"
#include "../View/keyexport.h"
#include "../View/keyimport.h"
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
    MainWindow* m_mainWindow;
    MainWindowModel* m_model;
    Launcher* m_launcher;
    KeyImport* m_import;
    //A FAIRE A LA MAIN
    void testCase_nr2();
    void testCase_u11();
    void testCase_u12();
    void testCase_nr1();
    //A FAIRE A LA MAIN

private Q_SLOTS:
    void testCase_u1();
    void testCase_u3();
    void testCase_u5();
    void testCase_u6();
    void testCase_u7();
    void testCase_u8();
    void testCase_u10();
    void testLoadConfig();
    void cleanupTestCase();
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
    Profile* p = new Profile(78766, "test");
    p->setConfigurationPath("/tmp");
    p->getConfigurationPath();
    p->setGPGExecutable("gpg");
    m_config->addProfile(p);
    m_config->setDefaultProfileId(78766);
    Launcher* launcher= new Launcher(m_app, m_config);
    m_launcher = launcher;
    MainWindowModel* model= new MainWindowModel(m_launcher, m_app, m_config, m_config->getDefaultProfile());
    m_model = model;
    MainWindow* mainWindow= new MainWindow(m_model);
    m_mainWindow = mainWindow;
    KeyImport* import = new KeyImport(m_mainWindow);
    m_import = import;
}

void MainTest::testCase_u1()
{
    m_model->getKeyManager()->getPubKeys();
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
    //QVERIFY_EXCEPTION_THROWN(launcher.addMainWindow(NULL, &mainWindow), IllegalArgumentException);
    //QVERIFY_EXCEPTION_THROWN(launcher.addMainWindow(m_config->getDefaultProfile(), NULL), IllegalArgumentException);
    launcher.addMainWindow(m_config->getDefaultProfile(), m_mainWindow);
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

}

void MainTest::testCase_u10()
{

    QVERIFY(m_model->getLauncher() == m_launcher);
    QVERIFY(m_model->getGuiPGApp() == m_app);
    QVERIFY(m_model->getConf() == m_config);
    QVERIFY(m_model->getProfile() == m_config->getDefaultProfile());
    //m_model->loadProfile(m_config->getDefaultProfileId(), m_mainWindow);
    //m_model->initKeyManager();
    QVERIFY(m_model->getKeyManager() != NULL);
}

void MainTest::testCase_u11()
{
    //A FAIRE A LA MAIN
    /*remove("/tmp/TEST");
    KeyExport keyExport(m_mainWindow);
    keyExport.exportFunction(KeyExport::EXPORT_FILE, "", "/tmp/TEST");
    QVERIFY(remove("/tmp/TEST") != -1);
    QVERIFY(keyExport.exportFunction(KeyExport::EXPORT_FILE, "", "/tmp/gaijgz/kjqnonzb/zzozop") == -1);
    QVERIFY(remove("/tmp/gaijgz/kjqnonzb/zzozop") == -1);
    QVERIFY(keyExport.exportFunction(KeyExport::EXPORT_FILE, "", "/etc/test") == -1);
    QVERIFY(remove("/etc/test") == -1);*/
}

void MainTest::testCase_u12()
{
    //A FAIRE A LA MAIN

}

void MainTest::testCase_nr1()
{
    //A FAIRE A LA MAIN
    /*remove("/tmp/TEST");
    KeyExport* keyExport = new KeyExport(m_mainWindow);
    keyExport->exportFunction(KeyExport::EXPORT_FILE, "", "/tmp/TEST");
    QVERIFY(remove("/tmp/TEST") != -1);*/
}

void MainTest::testCase_nr2()
{
    //A FAIRE A LA MAIN
    /*Profile* p = new Profile(1234, "test");
    p->setConfigurationPath("/tmp");
    p->setGPGExecutable("/usr/bin/gpg");
    m_config->addProfile(p);
    for (int i=0; i < 20; i++) {
        m_mainWindow->changeProfil(1);
        m_mainWindow->changeProfil(1234);
    }
    m_config->deleteProfile(p->getId());*/
}

void MainTest::testLoadConfig()
{
    Configuration config("../config.xml");
    QVERIFY(config.load() == true);
}

void MainTest::cleanupTestCase() {
    m_config->setDefaultProfileId(1);
    m_config->deleteProfile(78766);
}
QTEST_MAIN(MainTest)

#include "tst_maintest.moc"
