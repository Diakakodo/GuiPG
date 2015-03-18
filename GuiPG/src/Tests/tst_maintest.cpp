#include <QString>
#include <QtTest>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"
#include "../GPG/action.h"
#include "../Model/mainwindowmodel.h"
#include "../View/mainwindow.h"
#include "../View/keyexport.h"
#include <unistd.h>
#include <chrono>
#include <thread>

class MainTest : public QObject
{
    Q_OBJECT

public:
    MainTest();

private Q_SLOTS:
    void testCase_u11();
    void testCase_u13();
    void testCase_nr1();
    void testLoadConfig();

};

MainTest::MainTest()
{
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

    Configuration config("../config.xml");
    config.load();

    int argc = 2;
    char* argv[] = {"GuiPG", NULL};
    GuiPGApp app(argc, argv);
    Launcher launcher(&app, &config, config.getDefaultProfileId());
    MainWindowModel model(&launcher, &app, &config, config.getDefaultProfile());
    MainWindow mainWindow(&model);
    KeyExport keyExport(&mainWindow);
    keyExport.exportFunction(KeyExport::FILE, "", "/tmp/TEST");
    sleep(2);
    QVERIFY(remove("/tmp/TEST") != -1);
}

void MainTest::testLoadConfig()
{
    Configuration config("config.xml");
    QVERIFY(config.load() == true);
}

QTEST_MAIN(MainTest)

#include "tst_maintest.moc"
