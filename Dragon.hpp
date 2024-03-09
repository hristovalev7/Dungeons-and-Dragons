#ifndef DUNGEONS_AND_DRAGONS_DRAGON_HPP
#define DUNGEONS_AND_DRAGONS_DRAGON_HPP

#define INITIAL_DRAGON_STRENGTH 25
#define INITIAL_DRAGON_INTELLECT 25
#define INITIAL_DRAGON_HEALTH 50

#include <stdexcept>
#include "Entity.hpp"
#include "functions.hpp"

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

    void attack(Entity& target);
};


#endif //DUNGEONS_AND_DRAGONS_DRAGON_HPP
