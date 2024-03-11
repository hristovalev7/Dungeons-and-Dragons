#ifndef DUNGEONS_AND_DRAGONS_DRAGON_HPP
#define DUNGEONS_AND_DRAGONS_DRAGON_HPP

#include <iostream>
#include <stdexcept>
#include "Entity.hpp"
#include "functions.hpp"
#include "Constants.hpp"

class Dragon : public Entity
{
private:
    static unsigned int scales;
public:
    Dragon();

    Dragon(unsigned int level);

    void takeDamage(unsigned int amount) override;

    void basicAttack(Entity& target) override;

    void castASpell(Entity& target) override;

    void attack(Entity& target) override;
};


#endif //DUNGEONS_AND_DRAGONS_DRAGON_HPP
