#include "Item.hpp"

void Item::handleNothing()
{
    if (itemType == Nothing)
    {
        name = "";
        modifier = 0;
    }
}

Item::Item(const std::string& _name, const ItemType& _itemType, unsigned int _modifier) : name(_name), itemType(_itemType), modifier(_modifier)
{
    handleNothing();
}

std::string Item::getName() const
{
    return name;
}

ItemType Item::getItemType() const
{
    return itemType;
}

unsigned int Item::getModifier() const
{
    return modifier;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "Name: " << item.getName() << '\n';
    os << "Type: " << item.getItemType() << '\n';
    os << "Stat modifier: " << item.getModifier() << '\n';
    return os;
}


