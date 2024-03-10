#ifndef DUNGEONS_AND_DRAGONS_MAP_HPP
#define DUNGEONS_AND_DRAGONS_MAP_HPP

#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <random>
#include <filesystem>
#include "Matrix.hpp"
#include "Cell.hpp"
#include "functions.hpp"

class Map : public Matrix<Cell>
{
private:
    unsigned int level;
    unsigned int dragons;
    unsigned int treasures;

    std::pair<unsigned int, unsigned int> playerPosition;

    void printHeader() const;

    void printMaze() const;

    void createLevelFile(const std::string& fileName);

public:
    Map();

    Map(const Matrix<Cell>& matrix);

    void print() const override;

    void addConnection(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction);

    [[nodiscard]] bool canGo(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const;

    [[nodiscard]] unsigned int getTreasures() const;

    [[nodiscard]] unsigned int getDragons() const;

    [[nodiscard]] bool hasDragon(unsigned int i, unsigned int j) const;

    [[nodiscard]] bool hasTreasure(unsigned int i, unsigned int j) const;

    [[nodiscard]] bool isEmpty(unsigned int i, unsigned int j) const;

    [[nodiscard]] std::pair<unsigned int, unsigned int> getPlayerPosition() const;

    void setSymbol(unsigned int i, unsigned int j, char c);

    void generateMaze();

    void nextLevel();

    void movePlayer(const Direction& direction);
};


#endif //DUNGEONS_AND_DRAGONS_MAP_HPP
