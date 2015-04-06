#include <QString>
#include <QtTest>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"
#include "../GPG/action.h"
#include "../Model/mainwindowmodel.h"
#include "../View/mainwindow.h"
#include "../View/keyexport.h"
#include "../View/Profil/profilecreation.h"
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
    void testCase_u11();
    void testCase_u13();
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
    char* argv[] = {"/home/pierre/projet_pgp/GuiPG/build/GuiPG"};
    GuiPGApp* app = new GuiPGApp(argc, argv);
    m_app = app;
}

void MainTest::testCase_u11()
{
    Profile p(66, "Mister T");
    p.setConfigurationPath("/");
    QString s = p.getConfigurationPath();
    QVERIFY(p.getConfigurationPath() == "/");
    p.setGPGExecutable("/");
    s = p.getGPGExecutable();
    QVERIFY(p.getGPGExecutable() == "/");
    QVERIFY(p.getId() == 66);
    QVERIFY(p.getName() == "Mister T");
}

void MainTest::testCase_u13()
{
    QStringList interactions = (QStringList() << "1" << "2" << "3");
    Action a("test", QStringList(), QStringList(), interactions);
    QVERIFY(a.getCmd() == "test");
    QVERIFY(a.getArgs() == QStringList());
    QVERIFY(a.getOptions() == QStringList());
    QVERIFY(a.getInteractions() == interactions);
    QVERIFY(a.nextInteraction() == "1");
    QVERIFY(a.nextInteraction() == "2");
    QVERIFY(a.nextInteraction() == "3");
    //Vérifier que a.nextInteraction() lance une exception (qt 5.3 requis)
    //QVERIFY_EXCEPTION_THROWN(a.nextInteraction(), IllegalStateException);
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
    m_config->save();
    m_config->load();
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
