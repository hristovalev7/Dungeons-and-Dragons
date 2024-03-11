#ifndef DUNGEONS_AND_DRAGONS_CONSTANTS_HPP
#define DUNGEONS_AND_DRAGONS_CONSTANTS_HPP

#include "Item.hpp"

// Player
#define MAX_HEALTH 50

#define MAGE_INTELLECT 40
#define MAGE_STRENGTH 10

#define WARRIOR_INTELLECT 10
#define WARRIOR_STRENGTH 40

// Dragon
#define INITIAL_DRAGON_STRENGTH 25
#define INITIAL_DRAGON_INTELLECT 25
#define INITIAL_DRAGON_HEALTH 50

// Treasures
const Item TREASURES[9]{{"Mail armor",         Armor,  5},
                        {"Flimsy cloth armor", Armor,  1},
                        {"Plate armor",        Armor,  10},
                        {"Rusty sword",        Weapon, 1},
                        {"Giant sword",        Weapon, 25},
                        {"Daggers",            Weapon, 22},
                        {"Meteor",             Spell,  30},
                        {"A magic trick",      Spell,  1},
                        {"Arcane blast",       Spell,  25}
};

#endif //DUNGEONS_AND_DRAGONS_CONSTANTS_HPP
