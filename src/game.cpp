#include "game.h"

void round_init()
{
    std::cout << "round_init()\n";
}

void player_phase()
{
    std::cout << "player_phase()\n";
}

void round_end()
{
    std::cout << "round_end()\n";
}

// Base constructor
Game::Game(size_t n) : nb_players(n), players(new Player *[n])
{
    nb_steps = 3;
    steps = new func_ptr_t[nb_steps];
    steps[0] = round_init;
    steps[1] = player_phase;
    steps[2] = round_end;
    // Base initalisation
    // TODO
}

// Start method
void Game::start()
{
    // Launch of round
    for (size_t i = 0; i < nb_steps; i++)
    {
        steps[i]();
    }
    end();
}

// End method
void Game::end()
{
    // Do whatever we want
}
