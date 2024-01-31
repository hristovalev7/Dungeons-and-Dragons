#ifndef DUNGEONS_AND_DRAGONS_MAP_HPP
#define DUNGEONS_AND_DRAGONS_MAP_HPP

#include <iostream>
#include <stack>
#include <set>
#include <random>
#include "Graph.hpp"
#include "Matrix.hpp"

class Map : public Matrix<char>
{
private:
    unsigned int level;
    unsigned int dragons;
    unsigned int treasures;

    Graph graph;

    void printBorder() const;

    void printMaze() const;

public:
    Map(const Matrix<char>& matrix);

    void print() const override;

    void addConnection(const std::pair<unsigned int, unsigned int>& cell1, const std::pair<unsigned int, unsigned int>& cell2);

    [[nodiscard]] bool canGo(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const;

    void generateMaze();
};


#endif //DUNGEONS_AND_DRAGONS_MAP_HPP
