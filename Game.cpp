#include "Game.hpp"

Game::Game(const Map& _map, const Player& _player) : map(_map), player(_player), level(1)
{}

void Game::addTreasures()
{
    unsigned int numberOfTreasures{map.getTreasures()};
    for (int t{0}; t < numberOfTreasures; ++t)
    {
        unsigned int i{randomUnsignedInt(0, map.getRows() - 1)};
        unsigned int j{randomUnsignedInt(0, map.getColumns() - 1)};
        if (map.isEmpty(i, j))
        {
            map.setSymbol(i, j, 'T');
        }
        else
        {
            --t; //a.k.a generate a new random pair
        }
    }
}

void Game::addDragons()
{
    unsigned int numberOfDragons{map.getDragons()};
    for (int d{0}; d < numberOfDragons; ++d)
    {
        unsigned int i{randomUnsignedInt(0, map.getRows() - 1)};
        unsigned int j{randomUnsignedInt(0, map.getColumns() - 1)};
        if (map.isEmpty(i, j))
        {
            map.setSymbol(i, j, 'D');
        }
        else
        {
            --d; //a.k.a generate a new random pair
        }
    }
}

Direction Game::parseDirection(const std::string& input)
{
    if (input == "u")
    {
        return Up;
    }
    else if (input == "d")
    {
        return Down;
    }
    else if (input == "l")
    {
        return Left;
    }
    else if (input == "r")
    {
        return Right;
    }
    return Invalid;
}

void Game::movePlayer(const Direction& direction)
{
    std::pair<unsigned int, unsigned int> currentPosition{map.getPlayerPosition()};
    if (!map.canGo(currentPosition, direction))
    {
        std::cout << "You can't go there!\n";
        return;
    }

    map.movePlayer(direction);
    map.setSymbol(currentPosition.first, currentPosition.second, '.');
    std::pair<unsigned int, unsigned int> newPosition{map.getNeighbor(currentPosition, direction)};
    if (map.hasTreasure(newPosition.first, newPosition.second))
    {
        treasureHandler();
    }
    else if (map.hasDragon(newPosition.first, newPosition.second))
    {
        fight();
    }
    else if (map.isFinalDestination(newPosition.first, newPosition.second))
    {
        bool leveledUp{finalDestinationHandler()};
        if (leveledUp)
        {
            newPosition = std::make_pair(0, 0);
        }
    }
    map.setSymbol(newPosition.first, newPosition.second, 'P');
}

void Game::fight()
{
    std::cout << "Yikes! A dragon...\n";

    Entity* first{nullptr};
    Entity* second{nullptr};
    Entity* dragon{nullptr};

    determineFirstToAttack(first, second, dragon);

    while (first->isAlive() && second->isAlive())
    {
        first->attack(*second);
        if (second->isAlive())
        {
            second->attack(*first);
        }
    }

    delete dragon;

    fightAftermath();
}

void Game::determineFirstToAttack(Entity*& first, Entity*& second, Entity*& dragon)
{
    bool playerIsFirst = randomUnsignedInt(0, 1);
    if (playerIsFirst)
    {
        first = &player;
        second = new Dragon(level);
        dragon = second;
    }
    else
    {
        first = new Dragon(level);
        second = &player;
        dragon = first;
    }
}

void Game::fightAftermath()
{
    if (player.isAlive())
    {
        std::cout << "The dragon is dead!\n";
        std::cout << "You were healed for 50% of your max health!\n";
        player.heal(player.getMaxHealth() / 2);
    }
    else
    {
        std::cout << "You died :(\n";
    }
}

void Game::treasureHandler()
{
    Item item{TREASURES[randomUnsignedInt(0, 8)]};
    std::cout << "You've found a treasure!\n";
    std::cout << item;
    std::string input;
    if (player.has(item.getItemType()))
    {
        std::cout << "You already have a " << item.getItemType() << '\n';
        std::cout << player.get(item.getItemType());
        std::cout << "Equipping the newfound item will REPLACE the one you have currently!\n";
    }
    std::cout << "Would you like to equip the newfound item?\n";
    std::getline(std::cin, input);
    if (input == "yes" || input == "y")
    {
        player.equip(item);
    }
    else if (input != "no" && input != "n")
    {
        ensureValidResponse(input, item);
    }
}

void Game::ensureValidResponse(std::string& input, const Item& item)
{
    while (input != "yes" && input != "no" && input != "y" && input != "n")
    {
        std::cout << "Invalid response!\n";
        std::cout << "Type \"yes\" or \"y\" to equip\n";
        std::cout << "Type \"no\" or \"n\" to discard\n";
        std::getline(std::cin, input);
    }
    if (input == "yes" || input == "y")
    {
        player.equip(item);
    }
}

bool Game::finalDestinationHandler()
{
    std::cout << "You've reached the target location!\n";
    std::cout << "Would you like to advance to the next level?\n";
    std::string input;
    std::getline(std::cin, input);
    bool leveledUp{input == "yes"};
    if (leveledUp)
    {
        map.nextLevel();
        addDragons();
        addTreasures();
        player.levelUp();
        std::cin.ignore(); //"std::cin >>" doesn't discard the new line at the end
    }
    return leveledUp;
}

void Game::gameLoop()
{
    while (player.isAlive())
    {
        map.print();
        std::cout << "Where would you like to go?\n";
        std::string input;
        std::getline(std::cin, input);
        Direction direction{parseDirection(input)};
        while (direction == Invalid)
        {
            std::cout << "Invalid direction!\n";
            std::cout << "Try again!\n";
            std::getline(std::cin, input);
            direction = parseDirection(input);
        }
        movePlayer(direction);
    }
}

void Game::start()
{
    map.setSymbol(0, 0, 'P');
    addTreasures();
    addDragons();
    gameLoop();
}





