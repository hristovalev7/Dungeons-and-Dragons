#ifndef DUNGEONS_AND_DRAGONS_PLAYER_HPP
#define DUNGEONS_AND_DRAGONS_PLAYER_HPP

#include "Entity.hpp"
#include "Class.hpp"
#include "Constants.hpp"
#include "Item.hpp"

class Player : public Entity
{
private:
    Class characterClass;

    void initializeStats(const Class& _characterClass);

    Item weapon;
    Item spell;
    Item armor;

public:
    Player(const Class& _characterClass);

    [[nodiscard]] bool hasWeapon() const;

    [[nodiscard]] bool hasSpell() const;

    [[nodiscard]] bool hasArmor() const;

    void takeDamage(unsigned int amount) override;

    void basicAttack(Entity& target) override;

    void castASpell(Entity& target) override;

    void attack(Entity& target) override;

    void levelUp();
};


#endif //DUNGEONS_AND_DRAGONS_PLAYER_HPP
