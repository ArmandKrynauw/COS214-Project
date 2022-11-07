#include "UnitTest.cpp"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    Client::instance()->runTest();
    return RUN_ALL_TESTS();
}