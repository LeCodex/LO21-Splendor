#include "game.h"
// Base constructor
Game::Game(size_t n) : nb_players(n), players(new Player *[n])
{
    // Base initalisation

    // Board is auto generated

    // Players must be initiated with the addPlayer method

    // Deck must be generated manually

    // Noble deck generation :
    // TODO

    // Ressource deck generation :
    // TODO
}

Game::~Game()
{
    // Deleting the players
    for (size_t i = 0; i < nb_players; i++)
        delete players[i];
    delete[] players;
}

void Game::addPlayer(std::string name, int index)
{
    if (players[index] != NULL)
        throw "Joueur déjà créé";
    // wait for Player class to be created
    // players[index] = new Player(name);
}
