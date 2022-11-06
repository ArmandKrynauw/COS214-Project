#include "UnitTest.cpp"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    Client::instance()->runTest();

        json data = WarEngine::instance()->getCountryStats();
        std::cout << data["data"][0]["totalUnits"] << std::endl;
        //std::cout << data["data"][1]["resources"] <<std::endl;
        //std::cout << data["day"] << std::endl;
        //std::cout << data["numberOfCountries"] << std::endl;
        //std::cout << data["numberOfAlliances"] << std::endl;

    return RUN_ALL_TESTS();
}