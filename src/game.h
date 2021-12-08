#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <vector>
#include "board.h"
#include "player.h"
#include "deck.h"
#include <iostream>

class Game
{
private:
    std::vector<Deck> decks;
    Board board;
    size_t nb_players;
    Player **players;
    Game(size_t n);

public:
    ~Game();

    // Deletion of the assign and copy constructor
    Game(Game &) = delete;
    Game &operator=(const Game &) = delete;

    // Singleton getter
    static Game *getInstance(size_t n);

    // Setters
    void addPlayer(std::string, int);

    // Getters
    Board &getBoard() { return board; }
    Player &getPlayer(int i)
    {
        if (i >= nb_players)
            throw "Index out of bound";
        return *players[i];
    }
    Deck &getDeck(int i)
    {
        if (i >= decks.size())
            throw "Index out of bound";
        return decks[i];
    }

    // Inner classes
    class Handler
    {
    private:
        Game *instance;

    public:
    };
};

#endif