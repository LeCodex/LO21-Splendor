#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <vector>
#include "board.h"
#include "ResourceCard.h"
#include "Player.h"
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

        // Inner classes
        struct Handler
        {
            Game *instance;
            Handler() : instance(nullptr) {}
            ~Handler() { delete instance; }
        };

        static Handler handler;
    protected:
        Board board;

        size_t nb_players;
        Player **players;

        Game(size_t n);

        virtual ~Game();

    public:
        // Deletion of the assign and copy constructor
        Game(const Game &) = delete;
        Game &operator=(const Game &) = delete;

        // Singleton getter
        static Game &createInstance(size_t n)
        {
            delete handler.instance;
            handler.instance = new Game(n);
            return *handler.instance;
        }

        static Game &getInstance()
        {
            if (handler.instance == nullptr)
                throw "No instance created\n";
            return *handler.instance;
        }

        // Setters
        virtual void addPlayer(std::string, bool, int);

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

        // Fonction de service pour acheter une carte de manière générale
        bool buyCard(const ResourceCard &card, Player &p);
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

        // Le joueur retourne un jeton à la banque
        bool returnToken(Token color, Player& p);

        // Le joueur choisit un noble à prendre
        bool chooseNoble(const NobleCard& card, Player& p);

        // Fonction appelée pour fait jouer l'IA
        void playAI(Splendor::Player &p, int level);

        // Fonction appelée quand l'IA a trop de tokens
        void returnTokenAI(Splendor::Player &p);
    };

    class CitiesGame : public Game
    {
    private:
        Deck<CitiesCard> cities;

        CitiesGame(size_t n): Game(n){}
        // Inner classes
        struct Handler
        {
            CitiesGame *instance;
            Handler() : instance(nullptr) {}
            ~Handler() { delete instance; }
        };

        static Handler handler;
    public:
        // Singleton getter
        static CitiesGame &createInstance(size_t n)
        {
            delete handler.instance;
            handler.instance = new CitiesGame(n);
            return *handler.instance;
        }

        static CitiesGame &getInstance()
        {
            if (handler.instance == nullptr)
                throw "No instance created\n";
            return *handler.instance;
        }

        void addPlayer(std::string, bool, int) override;
        void cardDistribution() override;

        // Deletion of the assign and copy constructor
        CitiesGame(const CitiesGame &) = delete;
        CitiesGame &operator=(const CitiesGame &) = delete;
    };
}

#endif
