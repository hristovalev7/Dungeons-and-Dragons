#include "Item.hpp"

Item::Item(const std::string& _name, const ItemType& _itemType, unsigned int _modifier) : name(_name), itemType(_itemType), modifier(_modifier)
{}

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
