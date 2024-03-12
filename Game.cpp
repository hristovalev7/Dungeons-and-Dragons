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
            map.addTreasure(i, j);
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
            map.addDragon(i, j);
        }
        else
        {
            --d; //a.k.a generate a new random pair
        }
    }
}

void Game::handleExit()
{
    std::cout << "Where would you like to save your progress?\n";
    std::string file;
    std::getline(std::cin, file);
    save(file);
    std::cout << "Progress saved in " << file;
    exit(0);
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
    else if (input == "exit")
    {
        handleExit();
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
        map.removeDragon(map.getPlayerPosition().first, map.getPlayerPosition().second);
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
    map.removeTreasure(map.getPlayerPosition().first, map.getPlayerPosition().second);
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
    bool result{true};
    std::cout << "Type \"new game\" to start a new game or type \"load <filename>\" to continue playing\n";
    std::string input1;
    std::string input2;
    std::getline(std::cin, input1, ' ');
    std::getline(std::cin, input2, '\n');
    if (input1 == "load" && !input2.empty())
    {
        load(input2);
    }
    else if (input1 == "new" && input2 == "game")
    {
        characterCreation();
        map.generateMaze();
        addTreasures();
        addDragons();
    }
    map.setSymbol(0, 0, 'P');
    gameLoop();
}

void Game::save(const std::string& file)
{
    std::ofstream saveFile(file, std::ios::out | std::ios::trunc);
    if (saveFile.good())
    {
        saveFile << player.getClass() << ' ' << player.getCurrentHealth() << ' ' << player.getMaxHealth() << ' ' << player.getIntellect() << ' ' << player.getStrength() << '\n';
        saveFile << map.getRows() << ' ' << map.getColumns() << ' ' << map.getDragons() << ' ' << map.getTreasures() << ' ' << level << '\n';
        saveFile << player.get(Armor).getName() << ' ' << player.get(Armor).getItemType() << ' ' << player.get(Armor).getModifier() << '\n';
        saveFile << player.get(Weapon).getName() << ' ' << player.get(Weapon).getItemType() << ' ' << player.get(Weapon).getModifier() << '\n';
        saveFile << player.get(Spell).getName() << ' ' << player.get(Spell).getItemType() << ' ' << player.get(Spell).getModifier() << '\n';
        for (const std::pair<unsigned int, unsigned int>& d: map.getDragonPositions())
        {
            saveFile << d.first << ' ' << d.second << ' ';
        }
        saveFile << '\n';
        for (const std::pair<unsigned int, unsigned int>& t: map.getTreasurePositions())
        {
            saveFile << t.first << ' ' << t.second << ' ';
        }
        saveFile << '\n';
    }
    for (int i{0}; i < map.getRows(); ++i)
    {
        for (int j{0}; j < map.getColumns(); ++j)
        {
            if (saveFile.good())
            {
                saveFile << map.getElement(i, j).up << map.getElement(i, j).down << map.getElement(i, j).left << map.getElement(i, j).right;
            }
            saveFile << ' ';
        }
        saveFile << '\n';
    }
    saveFile.close();
}

void Game::load(const std::string& file)
{
    std::ifstream saveFile(file, std::ios::in);
    std::string playerClass;
    unsigned int currentHealth, maxHealth, intellect, strength, rows, columns, dragons, treasures, _level;
    Cell currentCell{};
    if (saveFile.good())
    {
        saveFile >> playerClass >> currentHealth >> maxHealth >> intellect >> strength >> rows >> columns >> dragons >> treasures >> _level;
    }
    Item armor{"", Armor, 0};
    Item weapon{"", Weapon, 0};
    Item spell{"", Spell, 0};
    saveFile >> armor >> weapon >> spell;
    Matrix<Cell> matrix(rows, columns);
    std::set<std::pair<unsigned int, unsigned int>> loadedDragonPositions;
    std::set<std::pair<unsigned int, unsigned int>> loadedTreasurePositions;
    for (int d{0}; d < dragons; ++d)
    {
        unsigned int i;
        unsigned int j;
        saveFile >> i;
        saveFile >> j;
        loadedDragonPositions.emplace(i, j);
    }
    for (int t{0}; t < treasures; ++t)
    {
        unsigned int i;
        unsigned int j;
        saveFile >> i;
        saveFile >> j;
        loadedTreasurePositions.emplace(i, j);
    }
    for (int i{0}; i < rows && saveFile.good(); ++i)
    {
        for (int j{0}; j < columns && saveFile.good(); ++j)
        {
            char up, down, left, right;
            saveFile >> up >> down >> left >> right;
            currentCell = {(bool) (up - '0'), (bool) (down - '0'), (bool) (left - '0'), (bool) (right - '0'), '.'};
            matrix.setElement(i, j, currentCell);
        }
    }
    Map loadedMap(matrix, loadedDragonPositions, loadedTreasurePositions, _level);
    Class loadedClass{identifyClass(playerClass)};
    Player loadedPlayer(loadedClass, weapon, armor, spell, currentHealth, maxHealth, strength, intellect);
    for (std::pair<unsigned int, unsigned int> d: loadedDragonPositions)
    {
        loadedMap.setSymbol(d.first, d.second, 'D');
    }
    for (std::pair<unsigned int, unsigned int> t: loadedTreasurePositions)
    {
        loadedMap.setSymbol(t.first, t.second, 'T');
    }
    level = _level;
    map = loadedMap;
    player = loadedPlayer;
    saveFile.close();
}

void Game::characterCreation()
{
    std::cout << "There are two classes available: Warrior and Mage\n";
    std::cout << "Which on would you like to play with?\n";
    std::string input;
    std::getline(std::cin, input);
    Class playerClass{identifyClass(input)};
    Player newPlayer(playerClass);
}






