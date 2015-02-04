#include <QString>
#include <QtTest>
#include "../Profile/profile.h"
#include "../action.h"

class MainTest : public QObject
{
    Q_OBJECT

public:
    MainTest();

private Q_SLOTS:
    void testCase1();
    void testCase2();

};

MainTest::MainTest()
{
}

void MainTest::testCase1()
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

void MainTest::testCase2()
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
    // TODO Vérifier que a.nextInteraction() lance une exception
}

QTEST_MAIN(MainTest)

#include "tst_maintest.moc"
