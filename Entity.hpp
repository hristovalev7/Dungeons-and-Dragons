#ifndef DUNGEONS_AND_DRAGONS_ENTITY_HPP
#define DUNGEONS_AND_DRAGONS_ENTITY_HPP

#include <algorithm>

class Entity
{
private:
    unsigned int strength;
    unsigned int intellect;
    unsigned int currentHealth;
    unsigned int maxHealth;

public:
    Entity(unsigned int _strength, unsigned int _intellect, unsigned int _maxHealth);

    void takeTrueDamage(unsigned int damage);

    void heal(unsigned int amount);

    void increaseMaxHealth(unsigned int amount);

    void increaseIntellect(unsigned int amount);

    void increaseStrength(unsigned int amount);
};


#endif //DUNGEONS_AND_DRAGONS_ENTITY_HPP
