#include "Dragon.hpp"

Dragon::Dragon() : Entity(INITIAL_DRAGON_STRENGTH, INITIAL_DRAGON_INTELLECT, INITIAL_DRAGON_HEALTH)
{}

void Dragon::takeDamage(unsigned int amount)
{
    amount = amount - scales / 100 * amount;
    takeTrueDamage(amount);
}

void Dragon::basicAttack(Entity& target)
{
    target.takeDamage(getStrength());
}

void Dragon::castASpell(Entity& target)
{
    target.takeDamage(getIntellect());
}

void Dragon::attack(Entity& target)
{
    unsigned int attackType{randomUnsignedInt(0, 1)};
    switch (attackType)
    {
        case 0:
            basicAttack(target);
            break;
        case 1:
            castASpell(target);
            break;
        default:
            throw std::runtime_error("Invalid attack type");
    }
}

Dragon::Dragon(unsigned int level) : Entity(INITIAL_DRAGON_STRENGTH + 10 * level, INITIAL_DRAGON_INTELLECT + 10 * level, INITIAL_DRAGON_HEALTH + 10 * level)
{
    scales = (unsigned int) (scales * std::pow(1 + (double) 15 / 100, level));
}



