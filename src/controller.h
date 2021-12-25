#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Splendor.h"
#include "game.h"
#include "action.h"
#include <iostream>

namespace Splendor
{
    class Controller
    {
    protected:
        // View v;
        size_t actual_player = 0;
        std::vector<void (*)()> actions;

    public:
        Controller() = default;

        virtual void initiateGame() = 0;
        virtual void launch() = 0;
        virtual void playTurn(size_t) = 0;
        // Verifiy if the specified player has won
        virtual bool hasWon(size_t) = 0;
        // Verify if the specified player can receive a noble
        virtual void nobleVerification(size_t) = 0;
    };

    class TextualController : public Controller
    {
    private:
    public:
        TextualController() : Controller()
        {
            // Add the actions func
        }
        void initiateGame();
        void printGame();
        bool hasWon(size_t);
        void launch();
        void playTurn(size_t);
        void nobleVerification(size_t);
    };
}

#endif