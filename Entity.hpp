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

    [[nodiscard]] unsigned int getStrength() const;

    [[nodiscard]] unsigned int getIntellect() const;

    [[nodiscard]] unsigned int getCurrentHealth() const;

    [[nodiscard]] unsigned int getMaxHealth() const;

    void takeTrueDamage(unsigned int damage);

    void heal(unsigned int amount);

    void increaseMaxHealth(unsigned int amount);

    void increaseIntellect(unsigned int amount);

    void increaseStrength(unsigned int amount);

    virtual void takeDamage(unsigned int amount) = 0;

    virtual void basicAttack(Entity& target) = 0;

    virtual void castASpell(Entity& target) = 0;
};


#endif //DUNGEONS_AND_DRAGONS_ENTITY_HPP
