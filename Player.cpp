#include "Player.hpp"

void Player::initializeStats(const Class& _characterClass)
{
    increaseMaxHealth(MAX_HEALTH);
    switch (_characterClass)
    {
    case Mage:
        increaseIntellect(MAGE_INTELLECT);
        increaseStrength(MAGE_STRENGTH);
        break;
    case Warrior:
        increaseStrength(WARRIOR_STRENGTH);
        increaseIntellect(WARRIOR_INTELLECT);
        break;
    }
}

Player::Player(const Class& _characterClass) : Entity(0, 0, 0), characterClass(_characterClass), weapon("Sword", Weapon, 20), spell("Fireball", Spell, 20), armor("", Nothing, 0)
{
    initializeStats(_characterClass);
}

void Player::takeDamage(unsigned int amount)
{
    unsigned int postMitigationDamage{(unsigned int)(amount - (double)armor.getModifier() / 100 * amount)};
    std::cout << "You took " << postMitigationDamage << " damage from this attack\n";
    takeTrueDamage(postMitigationDamage);
}

void Player::basicAttack(Entity& target)
{
    std::cout << "You basic attacked the dragon for " << getStrength() + weapon.getModifier() << '\n';
    target.takeDamage(getStrength() + weapon.getModifier());
}

void Player::castASpell(Entity& target)
{
    std::cout << "You cast a spell that deals " << getIntellect() + spell.getModifier() << " damage\n";
    target.takeDamage(getIntellect() + spell.getModifier());
}

void Player::attack(Entity& target)
{
    std::cout << "How would you like to attack?\n";
    std::string input;
    std::getline(std::cin, input);
    if (input == "basic attack")
    {
        basicAttack(target);
    }
    else if (input == "cast a spell")
    {
        castASpell(target);
    }
    else
    {
        ensureValidAttack(input, target);
    }
}

void Player::levelUp()
{
    unsigned int points{30};
    std::cout << "You leveled up!\n";
    unsigned int strength;
    unsigned int intellect;
    unsigned int maxHealth;
    std::cout << "You can now distribute " << points << " points among your stats\n";
    while (points > 0)
    {
        std::cout << "How many points would you like to add to your strength?\n";
        std::cin >> strength;
        std::cout << "How many points would you like to add to your intellect?\n";
        std::cin >> intellect;
        std::cout << "How many points would you like to add to your max health?\n";
        std::cin >> maxHealth;
        if (strength + intellect + maxHealth > points)
        {
            std::cout << "You cannot spend over " << points << " points!\n";
        }
        else
        {
            points = points - (strength + intellect + maxHealth);
            increaseStrength(strength);
            increaseIntellect(intellect);
            increaseMaxHealth(maxHealth);
        }
    }
}

Item Player::get(const ItemType& type) const
{
    Item result{"", Nothing, 0};
    switch (type)
    {
    case Weapon:
        result = weapon;
        break;
    case Armor:
        result = armor;
        break;
    case Spell:
        result = spell;
        break;
    case Nothing:
        throw std::invalid_argument("Invalid argument given to Player::ger(const ItemType& type)");
    }
    return result;
}

void Player::equip(const Item& item)
{
    switch (item.getItemType())
    {
    case Weapon:
        weapon = item;
        break;
    case Armor:
        armor = item;
        break;
    case Spell:
        spell = item;
        break;
    case Nothing:
        throw std::invalid_argument("Cannot equip nothing! Player::equip(const Item& item)");
    }
}

bool Player::has(const ItemType& type) const
{
    bool result{false};
    switch (type)
    {
    case Weapon:
        result = weapon.getItemType() != Nothing;
        break;
    case Armor:
        result = armor.getItemType() != Nothing;
        break;
    case Spell:
        result = spell.getItemType() != Nothing;
        break;
    case Nothing:
        throw std::invalid_argument("Nothing given as an argument to Player::has(const Item& type)");
    }
    return result;
}

void Player::ensureValidAttack(std::string& input, Entity& target)
{
    while (input != "cast a spell" && input != "basic attack")
    {
        std::cout << "Invalid input!\n";
        std::cout << "Type \"basic attack\" to attack with your weapon(scales with strength and weapon modifier)\n";
        std::cout << "Type \"cast a spell\" to cas a spell(scales with intellect and spell modifier)\n";
        std::getline(std::cin, input);
    }
    if (input == "basic attack")
    {
        basicAttack(target);
    }
    else // input == "cast a spell"
    {
        castASpell(target);
    }
}

Class Player::getClass() const
{
    return characterClass;
}

Player::Player(const Class& _characterClass, const Item& _weapon, const Item& _armor, const Item& _spell, unsigned int currentHealth, unsigned int maxHealth, unsigned int strength,
               unsigned int intellect) : Entity(strength, intellect, maxHealth, currentHealth), weapon(_weapon), armor(_armor), spell(_spell), characterClass(_characterClass)
{
}

//Player::Player(const Class& _characterClass, const Item& _weapon, const Item& _armor, const Item& _spell) : characterClass(_characterClass), weapon(_weapon), spell(_spell), armor(_armor)
//{
//
//}
