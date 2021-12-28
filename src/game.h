#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <vector>
#include "board.h"
#include "Player.h"
#include "ResourceCard.h"
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
        static Game &createInstance(size_t n)
        {
            if (handler.instance == nullptr)
                handler.instance = new Game(n);
            return *handler.instance;
        }

        static Game &getInstance()
        {
            if (handler.instance == nullptr)
                throw "No instance created\n";
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

        size_t getNbPlayer() const { return nb_players; }

        // Actions

        // Verification
        bool canPlayerBuyCard(Player &p, const ResourceCard &card);
        int getRealCost(Player &p, const ResourceCard &card, Token t);

        // Le joueur p achete une carte qu'il a deja reservée
        bool buyReservedCard(const ResourceCard &card, Player &p);

        // Le joueur p achete une carte du plateau
        bool buyBoardCard(const ResourceCard &card, Player &p);

        // Le joueur reserve une carte
        bool reserveCenterCard(const ResourceCard &card, Player &p);
        bool reserveDrawCard(size_t i, Player &p);

        // Le joueur prend 2 jetons identiques
        bool takeTwoIdenticalToken(Token color, Player &p);

        // Le joueur prend 3 jetons diffèrents
        bool takeThreeDifferentToken(Token color1, Token color2, Token color3, Player &p);
    };
}
#endif