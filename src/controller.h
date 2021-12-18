#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Splendor.h"
#include "game.h"
#include <iostream>

namespace Splendor
{
    class Controller
    {
    protected:
        // View v;
        Game *game;

    public:
        Controller() = default;
        virtual ~Controller()
        {
            if (game)
                delete game;
        }

        virtual void initiateGame() = 0;
    };

    class TextualController : public Controller
    {
    private:
    public:
        void initiateGame()
        {
            // Ask for number of players
            std::cout << "Please enter the number of player that are playing.\n";

            // Store it
            int n;
            std::cin >> n;

            // Instanciate the game
            this->game = new Game(n);

            std::cout << "A " << n << " players game has been created.\n";

            // Adding n players
            for (size_t i = 0; i < n; i++)
            {
                string s;

                std::cout << "Please enter the name of player #" << i << "\n";
                std::cin >> s;

                game->addPlayer(s, i);
            }
        }
    };
}

#endif