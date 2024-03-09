#ifndef DUNGEONS_AND_DRAGONS_ITEM_HPP
#define DUNGEONS_AND_DRAGONS_ITEM_HPP

#include <string>
#include "ItemType.hpp"

class Item
{
private:
    std::string name;
    ItemType itemType;
    unsigned int modifier;

    void handleNothing();

public:
    Item(const std::string& _name, const ItemType& _itemType, unsigned int _modifier);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] ItemType getItemType() const;

    [[nodiscard]] unsigned int getModifier() const;
};


#endif //DUNGEONS_AND_DRAGONS_ITEM_HPP
