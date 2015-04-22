#include <QString>
#include <QtTest>
#include "../Profile/profile.h"
#include "../Profile/profilemanager.h"
#include "../Configuration/configuration.h"
#include "../GPG/action.h"
#include "../Model/mainwindowmodel.h"
#include "../Keys/primaseckey.h"
#include "../Keys/primapubkey.h"
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


private Q_SLOTS:
    void testCase_u1();
    void testCase_u2();
    void testCase_u3();
    void testCase_u4();
    void testCase_u5();
    void testCase_u6();
    void testCase_u7();
    void testCase_u8();
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
}


void MainTest::testCase_u1()
{
    QList<Profile*> profiles = m_config->getProfiles();
    m_config->addProfile(new Profile(1751, "test"));
    QVERIFY(profiles.length() == m_config->getProfiles().length() - 1);
    QVERIFY(m_config->getProfileById(1751) != nullptr);
    m_config->deleteProfile(1751);
    QVERIFY(m_config->getProfileById(1751) == nullptr);
    QVERIFY(profiles == m_config->getProfiles());
    qDebug() << "Classes de gestion de profil : OK!";
}

void MainTest::testCase_u2()
{
    PrimaSecKey primaSecKey(QString("1"), 1024, QString("aaa"), QString("6666666"), QDate(1,2,3), QDate(4,5,6));
    QVERIFY(primaSecKey.getExpirationDate() == QDate(4,5,6));
    Uid* uid = new Uid("1", QDate(1,2,3), QString(""), QString("bob"), QString("bob@bob.bob"));
    primaSecKey.addUid(uid);
    QVERIFY(primaSecKey.getUidList().contains(uid));
    QVERIFY(primaSecKey.hasPrimaSecKey() == false);
    PrimaPubKey* pubKey = new PrimaPubKey(QString("1"), QString("1"), 10, QString("RSA"), QString("66"), QDate(1,2,3), QDate(2,3,4), QString(""), QString(""));
    primaSecKey.setPrimaryPubKey(pubKey);
    QVERIFY(primaSecKey.hasPrimaSecKey() == true);
    QVERIFY(primaSecKey.getPrimarySecKey() == pubKey);
    SubSecKey* subSecKey = new SubSecKey(QString(""), 10, QString(), QString("15"), QDate(52,15,17));
    primaSecKey.addSubSecKey(subSecKey);
    QVERIFY(primaSecKey.getSubSecKeyList().contains(subSecKey));
    delete uid;
    delete pubKey;
    qDebug() << "Classe PrimaSecKey : OK!";
}

void MainTest::testCase_u3()
{
    Profile p(66, "Mister T");
    p.setConfigurationPath("/");
    QString s = p.getConfigurationPath();
    QVERIFY(p.getConfigurationPath() == "/");
    p.setGPGExecutable("gpg");
    QVERIFY(p.getGPGExecutable() == "gpg");
    QVERIFY(p.getId() == 66);
    QVERIFY(p.getName() == "Mister T");
    qDebug() << "Classe Profile : OK!";
}

void MainTest::testCase_u4()
{
    Launcher launcher(m_app, m_config);
    //qt 5.3 requis
    //QVERIFY_EXCEPTION_THROWN(launcher.addMainWindow(NULL, &mainWindow), IllegalArgumentException);
    //QVERIFY_EXCEPTION_THROWN(launcher.addMainWindow(m_config->getDefaultProfile(), NULL), IllegalArgumentException);
    launcher.addMainWindow(m_config->getDefaultProfile(), m_mainWindow);
    launcher.start();
    QVERIFY(launcher.profileIsLoad(m_config->getDefaultProfile()) != NULL);
    launcher.UnloadProfileWithWindow(m_config->getDefaultProfile());
    launcher.stop();
    while(launcher.isRunning());
    QVERIFY(launcher.alreadyRun() == false);
    qDebug() << "Classe Launcher : OK!";
}

void MainTest::testCase_u5()
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
    qDebug() << "Classe Action : OK!";
}

void MainTest::testCase_u6()
{
    GPGManager manager(m_config->getDefaultProfile());
    Action a("--version", QStringList(), QStringList());
    manager.setAction(a);
    manager.execute();
    qDebug() << "Classe GPGManager : OK!";
}

void MainTest::testCase_u7()
{
    PrimaPubKey primaPubKey(QString(), QString(""), 100, QString(), QString(), QDate(1,2,3), QDate(1,2,3), QString(), QString());
    QVERIFY(primaPubKey.getTrust() == QString(""));
    SubPubKey* subPubKey = new SubPubKey(QString(), QString(), 10, QString(), QString(), QDate(1,2,3), QDate(2,3,4), QString());
    primaPubKey.addSubPubKey(subPubKey);
    QVERIFY(primaPubKey.getSubPubKeyList().contains(subPubKey));
    Uid* uid = new Uid("1", QDate(1,2,3), QString(""), QString("bob"), QString("bob@bob.bob"));
    primaPubKey.addUid(uid);
    QVERIFY(primaPubKey.getUidList().contains(uid));
    primaPubKey.setPrimaryUid(uid);
    QVERIFY(primaPubKey.getPrimaryUid() == uid);
    QVERIFY(primaPubKey.hasPrimaSecKey() == false);
    PrimaSecKey* primaSecKey= new PrimaSecKey(QString("1"), 1024, QString("aaa"), QString("6666666"), QDate(1,2,3), QDate(4,5,6));
    primaPubKey.setPrimarySecKey(primaSecKey);
    QVERIFY(primaPubKey.hasPrimaSecKey() == true);
    QVERIFY(primaPubKey.getPrimarySecKey() == primaSecKey);
    qDebug() << "Classe PrimaPubKey : OK!";
}

void MainTest::testCase_u8()
{

    QVERIFY(m_model->getLauncher() == m_launcher);
    QVERIFY(m_model->getGuiPGApp() == m_app);
    QVERIFY(m_model->getConf() == m_config);
    QVERIFY(m_model->getProfile() == m_config->getDefaultProfile());
    QVERIFY(m_model->getKeyManager() != NULL);
    qDebug() << "Classe MainWindowModel : OK!";
}



void MainTest::cleanupTestCase() {
    m_config->setDefaultProfileId(1);
    m_config->deleteProfile(78766);
}
QTEST_MAIN(MainTest)

#include "tst_maintest.moc"
