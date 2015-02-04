#include "test_13.h"
#include "testmanager.h"
#include "../GPG/action.h"

Test_13::Test_13()
{

}

Test_13::~Test_13()
{

}

void Test_13::runTest() {
    QStringList interactions = (QStringList() << "1" << "2" << "3");
    Action a("test", QStringList(), QStringList(), interactions);
    TestManager::evaluateTest("13.1", a.getCmd() == "test");
    TestManager::evaluateTest("13.2", a.getArgs() == QStringList());
    TestManager::evaluateTest("13.3", a.getOptions() == QStringList());
    TestManager::evaluateTest("13.4", a.getInteractions() == interactions);
    TestManager::evaluateTest("13.5", a.nextInteraction() == "1");
    TestManager::evaluateTest("13.6", a.nextInteraction() == "2");
    TestManager::evaluateTest("13.7", a.nextInteraction() == "3");
    // TODO Vérifier que a.nextInteraction() lance une exception
}

