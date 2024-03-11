#include "Game.hpp"
#include "Player.hpp"

unsigned int Dragon::scales = 15;

int main()
{
    Map map;
    map.generateMaze();
    Player player(Warrior);
    Game game(map, player);
    game.start();
    return 0;
}
