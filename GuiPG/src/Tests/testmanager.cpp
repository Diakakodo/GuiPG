#include "testmanager.h"
#include <iostream>
#include "test_12.h"
#include "test_13.h"

TestManager::TestManager()
{

}

TestManager::~TestManager()
{

}

void TestManager::runTests() {
    std::cout << "###########DEBUT DES TESTS###########\n";

    Test_12 t12;
    t12.runTest();

    Test_13 t13;
    t13.runTest();

    std::cout << "###########FIN DES TESTS#############\n";
}

void TestManager::evaluateTest(std::string nb, bool test) {
    if (test) {
        std::cout << ("test " + nb + " passé !\n");
    } else {
        std::cout << ("test " + nb + " ECHEC !\n");
    }
}
