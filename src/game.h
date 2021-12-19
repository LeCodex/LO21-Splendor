#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <vector>
#include "board.h"
#include "player.h"
#include "Deck.h"
#include <iostream>
#include "rules.h"

namespace Splendor
{
    class Game
    {

    private:
        Deck<NobleCard> nobles;
        Deck<ResourceCard> resources;
        Board board;
        size_t nb_players;
        Player **players;

        // Inner classes
        struct Handler
        {
            Game *instance;
            Handler() : instance(nullptr) {}
            ~Handler() { delete instance; }
        };

        static Handler handler;

    public:
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
            handler.instance = nullptr;
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
        Deck<ResourceCard> &getResourceDeck()
        {
            return resources;
        }

        Deck<NobleCard> &getNobleDeck()
        {
            return nobles;
        }

        virtual void cardDistribution();
    };
}
#endif