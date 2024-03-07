#include "Entity.hpp"

Entity::Entity(unsigned int _strength, unsigned int _intellect, unsigned int _maxHealth) : strength(_strength), intellect(_intellect), currentHealth(_maxHealth), maxHealth(_maxHealth)
{}

void Entity::takeTrueDamage(unsigned int damage)
{
    currentHealth = currentHealth - damage;
}

void Entity::heal(unsigned int amount)
{
    currentHealth = std::min(currentHealth + amount, maxHealth);
}

void Entity::increaseMaxHealth(unsigned int amount)
{
    maxHealth = maxHealth + amount;
    currentHealth = currentHealth + amount;
}

void Entity::increaseIntellect(unsigned int amount)
{
    intellect = intellect + amount;
}

void Entity::increaseStrength(unsigned int amount)
{
    strength = strength + amount;
}


