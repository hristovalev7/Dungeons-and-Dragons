#include "functions.hpp"

unsigned int power(unsigned int x, unsigned int y)
{
    unsigned int result{1};
    for (int i{0}; i < y; ++i)
    {
        result = x * result;
    }
    return result;
}

unsigned int numberLength(unsigned int number)
{
    unsigned int result{};
    while (number > 9)
    {
        ++result;
        number = number / 10;
    }
    return result + 1;
}

std::string numberToString(unsigned int number)
{
    unsigned int length{numberLength(number)};
    std::string result;
    unsigned int multiplier{power(10, length - 1)};
    while (multiplier > 0)
    {
        result.push_back((char) ((number / multiplier) % 10 + '0'));
        multiplier = multiplier / 10;
    }
    return result;
}

unsigned int randomUnsignedInt(unsigned int from, unsigned int to)
{
    std::random_device randomDevice;
    std::default_random_engine generator(randomDevice());
    std::uniform_int_distribution<unsigned int> distribution(from, to);
    return distribution(generator);
}