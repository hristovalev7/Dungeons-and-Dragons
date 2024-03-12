#ifndef DUNGEONS_AND_DRAGONS_FUNCTIONS_HPP
#define DUNGEONS_AND_DRAGONS_FUNCTIONS_HPP

#include <string>
#include <random>
#include "Class.hpp"

unsigned int power(unsigned int x, unsigned int y);

unsigned int numberLength(unsigned int number);

std::string numberToString(unsigned int number);

unsigned int randomUnsignedInt(unsigned int from, unsigned int to);

Class identifyClass(const std::string& string);

#endif //DUNGEONS_AND_DRAGONS_FUNCTIONS_HPP
