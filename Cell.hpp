#ifndef DUNGEONS_AND_DRAGONS_CELL_HPP
#define DUNGEONS_AND_DRAGONS_CELL_HPP

#include <iostream>

struct MatrixCell
{
    bool up;
    bool down;
    bool left;
    bool right;
    char symbol;

    MatrixCell& operator=(const char c)
    {
        symbol = c;
        return *this;
    }
};

inline std::ostream& operator<<(std::ostream& os, const MatrixCell& matrixCell)
{
    return os << matrixCell.symbol;
}

#endif //DUNGEONS_AND_DRAGONS_CELL_HPP
