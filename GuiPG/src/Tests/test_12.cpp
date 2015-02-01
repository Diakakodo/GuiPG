#include "test_12.h"
#include "testmanager.h"
#include "../Profile/profile.h"

Test_12::Test_12()
{

}

Test_12::~Test_12()
{

}

void Test_12::runTest() {
    Profile p(66, "Mister T");
    p.setConfigurationPath("/");
    QString s = p.getConfigurationPath();
    TestManager::evaluateTest("12.1", s == "/");
    p.setGPGExecutable("/");
    s = p.getGPGExecutable();
    TestManager::evaluateTest("12.2", s == "/");
    TestManager::evaluateTest("12.3", p.getId() == 66);
    TestManager::evaluateTest("12.4", p.getName() == "Mister T");

}
