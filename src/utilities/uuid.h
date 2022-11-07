#ifndef UUID_H
#define UUID_H

#include <iostream>
#include <random>
#include <sstream>

namespace uuid {
static std::random_device rd;
static std::mt19937_64 gen(rd());
static std::uniform_int_distribution<> dis(0, 15);

std::string generate();
};  // namespace uuid

#endif  // UUID_H