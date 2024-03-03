#ifndef DUNGEONS_AND_DRAGONS_CELL_HPP
#define DUNGEONS_AND_DRAGONS_CELL_HPP

#include <iostream>

struct Cell
{
    bool up;
    bool down;
    bool left;
    bool right;
    char symbol;

    Cell& operator=(const char c)
    {
        symbol = c;
        return *this;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Cell& cell)
{
    return os << cell.symbol;
}

#endif //DUNGEONS_AND_DRAGONS_CELL_HPP
