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

inline std::istream& operator>>(std::istream& is, ItemType& itemType)
{
    std::string type;
    is >> type;
    if (type == "Armor")
    {
        itemType = Armor;
    }
    else if (type == "Weapon")
    {
        itemType = Weapon;
    }
    else if (type == "Spell")
    {
        itemType = Spell;
    }
    else
    {
        itemType = Nothing;
    }
    return is;
}

#endif //DUNGEONS_AND_DRAGONS_ITEMTYPE_HPP
