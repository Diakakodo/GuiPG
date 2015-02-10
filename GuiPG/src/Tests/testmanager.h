#ifndef TESTMANAGER_H
#define TESTMANAGER_H
#include <QObject>

class TestManager
{
public:
    TestManager();
    ~TestManager();
    void runTests();
    static void evaluateTest(std::string nb, bool test);
};

#endif // TESTMANAGER_H
