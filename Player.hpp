#ifndef DUNGEONS_AND_DRAGONS_PLAYER_HPP
#define DUNGEONS_AND_DRAGONS_PLAYER_HPP

#include <iostream>
#include "Entity.hpp"
#include "Class.hpp"
#include "Constants.hpp"
#include "Item.hpp"

class Player : public Entity
{
private:
    Class characterClass;

    Item weapon;
    Item spell;
    Item armor;

    void initializeStats(const Class& _characterClass);

    void ensureValidAttack(std::string& input, Entity& target);

public:
    Player() = delete;

    Player(const Class& _characterClass);

    Player(const Class& _characterClass, const Item& _weapon, const Item& _armor, const Item& _spell, unsigned int currentHealth, unsigned int maxHealth, unsigned int strength,
           unsigned int intellect);

    [[nodiscard]] Item get(const ItemType& type) const;

    [[nodiscard]] bool has(const ItemType& type) const;

    void equip(const Item& item);

    void takeDamage(unsigned int amount) override;

    void basicAttack(Entity& target) override;

    void castASpell(Entity& target) override;

    void attack(Entity& target) override;

    void levelUp();

    [[nodiscard]] Class getClass() const;
};


#endif //DUNGEONS_AND_DRAGONS_PLAYER_HPP
