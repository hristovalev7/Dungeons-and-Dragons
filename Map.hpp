#ifndef DUNGEONS_AND_DRAGONS_MAP_HPP
#define DUNGEONS_AND_DRAGONS_MAP_HPP

#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <random>
#include <filesystem>
#include <stdexcept>
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
    std::set<std::pair<unsigned int, unsigned int>> dragonPositions;
    std::set<std::pair<unsigned int, unsigned int>> treasurePositions;

    void printHeader() const;

    void printMaze() const;

    void createLevelFile(const std::string& fileName);

public:
    Map();

    Map(const Matrix<Cell>& matrix);

    Map(const Matrix<Cell>& matrix, const std::set<std::pair<unsigned int, unsigned int>>& _dragonPositions, const std::set<std::pair<unsigned int, unsigned int>>& _treasurePositions, unsigned int _level);

    void print() const override;

    void addConnection(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction);

    [[nodiscard]] bool canGo(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const;

    [[nodiscard]] unsigned int getTreasures() const;

    [[nodiscard]] unsigned int getDragons() const;

    bool hasDragon(unsigned int i, unsigned int j);

    bool hasTreasure(unsigned int i, unsigned int j);

    [[nodiscard]] bool isEmpty(unsigned int i, unsigned int j) const;

    [[nodiscard]] std::pair<unsigned int, unsigned int> getPlayerPosition() const;

    bool isFinalDestination(unsigned int i, unsigned int j);

    void setSymbol(unsigned int i, unsigned int j, char c);

    void generateMaze();

    void nextLevel();

    void movePlayer(const Direction& direction);

    void addDragon(unsigned int i, unsigned int j);

    void addTreasure(unsigned int i, unsigned int j);

    void removeDragon(unsigned int i, unsigned int j);

    void removeTreasure(unsigned int i, unsigned int j);

    [[nodiscard]] const std::set<std::pair<unsigned int, unsigned int>>& getDragonPositions() const;

    [[nodiscard]] const std::set<std::pair<unsigned int, unsigned int>>& getTreasurePositions() const;
};


#endif //DUNGEONS_AND_DRAGONS_MAP_HPP
