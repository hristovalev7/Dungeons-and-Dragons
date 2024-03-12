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
const Item TREASURES[9]{{"MailArmor",         Armor,  5},
                        {"FlimsyClothArmor", Armor,  1},
                        {"PlateArmor",        Armor,  10},
                        {"RustySword",        Weapon, 1},
                        {"GiantSword",        Weapon, 25},
                        {"Daggers",            Weapon, 22},
                        {"Meteor",             Spell,  30},
                        {"MagicTrick",      Spell,  1},
                        {"ArcaneBlast",       Spell,  25}
};

#endif //DUNGEONS_AND_DRAGONS_CONSTANTS_HPP
