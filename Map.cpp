#include "Map.hpp"

void Map::printHeader() const
{
    // getColumns() * 4 + 1 = getColumns() * 3 + (getColumns() - 1) + 2
    // getColumns() * 3 -> every cell is 3 chars wide
    // getColumns() - 1 -> the spaces/borders between the cells
    // + 2 -> the left and right borders
    for (int i{0}; i < getColumns() * 4 + 1; ++i)
    {
        std::cout << '#';
    }
    std::cout << '\n';
}

Map::Map() : Matrix(), level(1), dragons(0), treasures(0), playerPosition(0, 0)
{
    std::string fileName{"level1.txt"};
    std::ifstream file(fileName, std::ios::in);
    unsigned int rows;
    unsigned int columns;
    while (file.good())
    {
        file >> rows >> columns >> dragons >> treasures;
    }
    file.close();
    resize(rows, columns);
    fillMatrix('.');
    setSymbol(0, 0, 'P');
}

Map::Map(const Matrix<Cell>& matrix) : Matrix(matrix), level(1), dragons(0), treasures(0), playerPosition(0, 0)
{}

void Map::print() const
{
    printHeader();
    printMaze();
}

void Map::addConnection(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction)
{
    std::pair<unsigned int, unsigned int> neighbor{getNeighbor(cell, direction)};
    if (!inBounds(neighbor))
    {
        return;
    }
    Cell currentCell{getElement(cell.first, cell.second)};
    Cell neighborCell{getElement(neighbor.first, neighbor.second)};
    switch (direction)
    {
        case Up:
            currentCell.up = true;
            neighborCell.down = true;
            setElement(cell.first, cell.second, currentCell);
            setElement(neighbor.first, neighbor.second, neighborCell);
            break;
        case Down:
            currentCell.down = true;
            neighborCell.up = true;
            setElement(cell.first, cell.second, currentCell);
            setElement(neighbor.first, neighbor.second, neighborCell);
            break;
        case Left:
            currentCell.left = true;
            neighborCell.right = true;
            setElement(cell.first, cell.second, currentCell);
            setElement(neighbor.first, neighbor.second, neighborCell);
            break;
        case Right:
            currentCell.right = true;
            neighborCell.left = true;
            setElement(cell.first, cell.second, currentCell);
            setElement(neighbor.first, neighbor.second, neighborCell);
            break;
        case Invalid:
            throw std::logic_error("Invalid direction given to Map::addConnection()\n");
    }
}

void Map::generateMaze()
{
    std::stack<std::pair<unsigned int, unsigned int>> stack;
    std::set<std::pair<unsigned int, unsigned int>> visited;
    std::vector<Direction> eligible;
    stack.emplace(0, 0);
    visited.insert(std::make_pair(0, 0));
    while (visited.size() < getRows() * getColumns())
    {
        std::pair<unsigned int, unsigned int> currentCell{stack.top()};
        std::pair<unsigned int, unsigned int> neighborUp{getNeighbor(currentCell, Up)};
        std::pair<unsigned int, unsigned int> neighborDown{getNeighbor(currentCell, Down)};
        std::pair<unsigned int, unsigned int> neighborLeft{getNeighbor(currentCell, Left)};
        std::pair<unsigned int, unsigned int> neighborRight{getNeighbor(currentCell, Right)};
        if (inBounds(neighborUp) && !visited.contains(neighborUp))
        {
            eligible.emplace_back(Up);
        }
        if (inBounds(neighborDown) && !visited.contains(neighborDown))
        {
            eligible.emplace_back(Down);
        }
        if (inBounds(neighborLeft) && !visited.contains(neighborLeft))
        {
            eligible.emplace_back(Left);
        }
        if (inBounds(neighborRight) && !visited.contains(neighborRight))
        {
            eligible.emplace_back(Right);
        }
        if (eligible.empty())
        {
            stack.pop();
        }
        else
        {
            std::random_device randomDevice;
            std::default_random_engine generator(randomDevice());
            std::uniform_int_distribution<int> distribution(0, eligible.size() - 1);

            int randomNumber = distribution(generator);
            Direction direction = eligible[randomNumber];
            addConnection(currentCell, direction);
            visited.insert(getNeighbor(currentCell, direction));
            stack.push(getNeighbor(currentCell, direction));
            eligible.clear();
        }
    }
}

void Map::printMaze() const
{
    for (int i{0}; i < getRows(); ++i)
    {
        std::cout << '#';
        for (int j{0}; j < getColumns(); ++j)
        {
            std::cout << ' ' << getElement(i, j) << ' ';
            if (canGo(std::make_pair(i, j), Right))
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << '#';
            }
        }
        std::cout << '\n';
        std::cout << '#';
        for (int j{0}; j < getColumns(); ++j)
        {
            if (canGo(std::make_pair(i, j), Down))
            {
                if (!canGo(std::make_pair(i, j), Right) || !canGo(std::make_pair(i + 1, j), Right))
                {
                    std::cout << "   #";
                }
                else
                {
                    std::cout << "    ";
                }
            }
            else
            {
                std::cout << "####";
            }
        }
        std::cout << '\n';
    }
}

void Map::createLevelFile(const std::string& fileName)
{
    std::string previousLevelName{"level"};
    previousLevelName = previousLevelName + numberToString(level - 1);
    previousLevelName.append(".txt");

    std::ifstream previousLevel(previousLevelName, std::ios::in);

    unsigned int newLevelRows{};
    unsigned int newLevelColumns{};
    unsigned int newLevelDragons{};
    unsigned int newLevelTreasures{};

    while (previousLevel.good())
    {
        previousLevel >> newLevelRows >> newLevelColumns >> newLevelDragons >> newLevelTreasures;
    }

    previousLevel.close();

    newLevelRows = newLevelRows + getRows();
    newLevelColumns = newLevelColumns + getColumns();
    newLevelDragons = newLevelDragons + dragons;
    newLevelTreasures = newLevelTreasures + treasures;

    std::ofstream newLevel(fileName, std::ios::out);
    if (newLevel.good())
    {
        newLevel << newLevelRows << ' ' << newLevelColumns << ' ' << newLevelDragons << ' ' << newLevelTreasures;
    }

    newLevel.close();
}

bool Map::canGo(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const
{
    Cell currentCell = getElement(cell.first, cell.second);
    bool result{false};
    switch (direction)
    {
        case Up:
            result = currentCell.up;
            break;
        case Down:
            result = currentCell.down;
            break;
        case Left:
            result = currentCell.left;
            break;
        case Right:
            result = currentCell.right;
            break;
        case Invalid:
            throw std::logic_error("Invalid direction given to Map::canGo()\n");
    }
    return result;
}

unsigned int Map::getTreasures() const
{
    return treasures;
}

unsigned int Map::getDragons() const
{
    return dragons;
}

bool Map::hasDragon(unsigned int i, unsigned int j)
{
    return dragonPositions.contains({i, j});
}

bool Map::hasTreasure(unsigned int i, unsigned int j)
{
    return treasurePositions.contains({i, j});
}

bool Map::isEmpty(unsigned int i, unsigned int j) const
{
    return getElement(i, j).symbol == '.';
}

void Map::setSymbol(unsigned int i, unsigned int j, char c)
{
    setElement(i, j, {getElement(i, j).up, getElement(i, j).down, getElement(i, j).left, getElement(i, j).right, c});
}

void Map::nextLevel()
{
    unsigned int newLevel{level + 1};

    std::string fileName{"level"};
    fileName = fileName + numberToString(newLevel);
    fileName.append(".txt");

    std::filesystem::path filePath(fileName.c_str());
    if (!std::filesystem::exists(filePath))
    {
        createLevelFile(fileName);
    }

    std::ifstream file(fileName, std::ios::in);
    unsigned int rows{};
    unsigned int columns{};
    unsigned int levelTreasures{};
    unsigned int levelDragons{};
    while (file.good())
    {
        file >> rows >> columns >> levelDragons >> levelTreasures;
    }
    file.close();

    Matrix<Cell> matrix(rows, columns);
    matrix.fillMatrix('.');
    Map map(matrix);
    map.generateMaze();
    *this = map;
    level = newLevel;
    dragons = levelDragons;
    treasures = levelTreasures;
    setSymbol(0, 0, 'P');
}

void Map::movePlayer(const Direction& direction)
{
    std::pair<unsigned int, unsigned int> newPosition{getNeighbor(playerPosition, direction)};
    if (inBounds(newPosition))
    {
        playerPosition = newPosition;
    }
    else
    {
        std::cout << "You can't go there!\n";
    }
}

std::pair<unsigned int, unsigned int> Map::getPlayerPosition() const
{
    return playerPosition;
}

bool Map::isFinalDestination(unsigned int i, unsigned int j)
{
    return (i == getRows() - 1) && (j == getColumns() - 1);
}

void Map::addDragon(unsigned int i, unsigned int j)
{
    dragonPositions.emplace(i, j);
    setSymbol(i, j, 'D');
}

void Map::addTreasure(unsigned int i, unsigned int j)
{
    treasurePositions.emplace(i, j);
    setSymbol(i, j, 'T');
}

void Map::removeDragon(unsigned int i, unsigned int j)
{
    dragonPositions.erase({i, j});
}

void Map::removeTreasure(unsigned int i, unsigned int j)
{
    treasurePositions.erase({i, j});
}

const std::set<std::pair<unsigned int, unsigned int>>& Map::getDragonPositions() const
{
    return dragonPositions;
}

const std::set<std::pair<unsigned int, unsigned int>>& Map::getTreasurePositions() const
{
    return treasurePositions;
}

Map::Map(const Matrix<Cell>& matrix, const std::set<std::pair<unsigned int, unsigned int>>& _dragonPositions, const std::set<std::pair<unsigned int, unsigned int>>& _treasurePositions, unsigned int _level)
        : Matrix<Cell>(matrix),
          dragonPositions(_dragonPositions), treasurePositions(_treasurePositions), level(_level),
          dragons(_dragonPositions.size()), treasures(_treasurePositions.size()),
          playerPosition({0, 0})
{}


