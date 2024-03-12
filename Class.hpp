#ifndef DUNGEONS_AND_DRAGONS_CLASS_HPP
#define DUNGEONS_AND_DRAGONS_CLASS_HPP

#include <iostream>

enum Class
{
    Mage,
    Warrior,
};

inline std::ostream& operator<<(std::ostream& os, const Class& c)
{
    switch (c)
    {
        case Mage:
            os << "Mage";
            break;
        case Warrior:
            os << "Warrior";
            break;
    }
    return os;
}

#endif //DUNGEONS_AND_DRAGONS_CLASS_HPP
