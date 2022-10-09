#ifndef UUID_H
#define UUID_H

#include <random>
#include <sstream>
#include <iostream>

namespace uuid {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    std::string generate();
};

#endif // UUID_H