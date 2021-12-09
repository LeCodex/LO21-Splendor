#include "game.h"

int main()
{
    Game &g = Game::getInstance(3);
    g.addPlayer("joueur#0", 0);
    return 0;
}