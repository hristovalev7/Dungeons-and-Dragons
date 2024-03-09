#include "Map.hpp"
#include "Dragon.hpp"

unsigned int Dragon::scales = 15;

int main()
{
    Map map;
    map.generateMaze();
    map.print();
    map.nextLevel();
    map.print();
    return 0;
}
