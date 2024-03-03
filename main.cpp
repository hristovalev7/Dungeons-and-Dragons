#include "Matrix.hpp"
#include "Map.hpp"

int main()
{
    Map map;
    map.generateMaze();
    map.print();
    map.nextLevel();
    map.print();
    return 0;
}
