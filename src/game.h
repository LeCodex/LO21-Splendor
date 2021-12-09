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

public:
    // Inner classes
    struct Handler
    {
        Game *instance;
        Handler() : instance(nullptr) {}
        ~Handler() { delete instance; }
    };

    static Handler handler;

    Game(size_t n);

    ~Game();

    // Deletion of the assign and copy constructor
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    // Singleton getter
    static Game &getInstance(size_t n)
    {
        if (handler.instance == nullptr)
            handler.instance = new Game(n);
        return *handler.instance;
    }

    // Singleton deleter
    static void deleteInstance()
    {
        delete handler.instance;
    }

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
};

#endif