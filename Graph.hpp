#ifndef DUNGEONS_AND_DRAGONS_GRAPH_HPP
#define DUNGEONS_AND_DRAGONS_GRAPH_HPP

#include "Matrix.hpp"
#include "Direction.hpp"

class Graph : Matrix<bool>
{
public:

    Graph(size_t rows, size_t columns);

    [[nodiscard]] bool canGo(unsigned int i, unsigned int j, const Direction& direction, unsigned int rows, unsigned int columns) const;

    void addEdge(const std::pair<unsigned int, unsigned int>& node1, const std::pair<unsigned int, unsigned int>& node2, unsigned int matrixColumns);
};


#endif //DUNGEONS_AND_DRAGONS_GRAPH_HPP
