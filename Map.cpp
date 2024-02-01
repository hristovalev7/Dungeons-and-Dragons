#include "Map.hpp"

typedef std::pair<unsigned int, unsigned int> Cell;

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

Map::Map(const Matrix<char>& matrix) : Matrix(matrix), level(1), dragons(0), treasures(0), graph(matrix.getRows(), matrix.getColumns())
{
}

void Map::print() const
{
    printHeader();
    printMaze();
}

void Map::addConnection(const std::pair<unsigned int, unsigned int>& cell1, const std::pair<unsigned int, unsigned int>& cell2)
{
    graph.addEdge(cell1, cell2, getColumns());
}

void Map::generateMaze()
{
    std::stack<Cell> stack;
    std::set<Cell> visited;
    std::vector<Direction> eligible;
    stack.emplace(0, 0);
    visited.insert(std::make_pair(0, 0));
    while (visited.size() < getRows() * getColumns())
    {
        Cell currentCell{stack.top()};
        Cell neighborUp{getNeighbor(currentCell, Up)};
        Cell neighborDown{getNeighbor(currentCell, Down)};
        Cell neighborLeft{getNeighbor(currentCell, Left)};
        Cell neighborRight{getNeighbor(currentCell, Right)};
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
            addConnection(currentCell, getNeighbor(currentCell, direction));
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

bool Map::canGo(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const
{
    return graph.canGo(cell.first, cell.second, direction, getRows(), getColumns());
}

