#include "game.h"

void Splendor::CitiesGame::addPlayer(std::string name, bool ai, int index)
{
    if (players[index] != nullptr)
        throw "Joueur déjà créé";
    std::cout << "Player \"" << name << "\" has been added to [" << index << "]\n";
    players[index] = (Player*)new CitiesPlayer(name, ai);
}
