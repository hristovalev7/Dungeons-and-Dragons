#ifndef DUNGEONS_AND_DRAGONS_MAP_HPP
#define DUNGEONS_AND_DRAGONS_MAP_HPP

#include <iostream>
#include <stack>
#include <set>
#include <random>
#include "Matrix.hpp"
#include "Cell.hpp"
#include "functions.hpp"

class Map : public Matrix<MatrixCell>
{
private:
    unsigned int level;
    unsigned int dragons;
    unsigned int treasures;

    void printHeader() const;

    void printMaze() const;

public:
    Map(const Matrix<MatrixCell>& matrix);

    void print() const override;

    void addConnection(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction);

    [[nodiscard]] bool canGo(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const;

    void generateMaze();

    void nextLevel();
};


#endif //DUNGEONS_AND_DRAGONS_MAP_HPP
