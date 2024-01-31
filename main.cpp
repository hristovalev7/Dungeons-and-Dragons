#include "Matrix.hpp"
#include "Map.hpp"

int main()
{
    Matrix<char> matrix(7, 7);
    matrix.fillMatrix('.');
    Map map(matrix);
    map.generateMaze();
    map.print();
    return 0;
}
