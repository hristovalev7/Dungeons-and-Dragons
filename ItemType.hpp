#ifndef DUNGEONS_AND_DRAGONS_ITEMTYPE_HPP
#define DUNGEONS_AND_DRAGONS_ITEMTYPE_HPP

#include <iostream>

enum ItemType
{
    Weapon,
    Spell,
    Armor,
    Nothing
};

inline std::ostream& operator<<(std::ostream& os, const ItemType& itemType)
{
    switch (itemType)
    {
        case Weapon:
            os << "Weapon";
            break;
        case Spell:
            os << "Spell";
            break;
        case Armor:
            os << "Armor";
            break;
        case Nothing:
            os << "Nothing";
            break;
    }
    return os;
}

#endif //DUNGEONS_AND_DRAGONS_ITEMTYPE_HPP
