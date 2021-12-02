#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <vector>
#include "board.h"
#include "player.h"
#include <iostream>

typedef void (*func_ptr_t)(); // a function pointer

class Game
{
private:
    std::vector<int> decks;
    Board *board;
    size_t nb_players;
    Player **players;
    // List of round steps
    func_ptr_t *steps;
    size_t nb_steps;

public:
    Game(size_t n);
    void start();
    void end();
};

#endif