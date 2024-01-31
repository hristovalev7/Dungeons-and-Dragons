#include "Graph.hpp"

bool Graph::canGo(unsigned int i, unsigned int j, const Direction& direction, unsigned int columns) const
{
    switch (direction)
    {
        case Up:
            return getElement(i * columns + j, i * columns + j - columns);
        case Down:
            return getElement(i * columns + j, i * columns + j + columns);
        case Left:
            return getElement(i * columns + j, i * columns + j - 1);
        case Right:
            return getElement(i * columns + j, i * columns + j + 1);
    }
}

void Graph::addEdge(const std::pair<unsigned int, unsigned int>& node1, const std::pair<unsigned int, unsigned int>& node2, unsigned int matrixColumns)
{
    setElement(node1.first * matrixColumns + node1.second, node2.first * matrixColumns + node2.second, true);
    setElement(node2.first * matrixColumns + node2.second, node1.first * matrixColumns + node1.second, true);
}

Graph::Graph(size_t rows, size_t columns) : Matrix(rows * columns, rows * columns)
{
    for (int i{0}; i < rows; ++i)
    {
        setElement(i, i, true);
    }
}

