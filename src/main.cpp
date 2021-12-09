#include "game.h"

int main()
{
    Game &g = Game::getInstance(3);
    g.addPlayer("joueur#0", 0);
    g.deleteInstance();
    return 0;
}