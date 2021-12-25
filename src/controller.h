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
        size_t actual_player = 0;

    public:
        Controller() = default;

        virtual void initiateGame() = 0;
        virtual void launch() = 0;
        virtual void playTurn(size_t) = 0;
        // Verifiy if the specified player has won
        virtual bool hasWon(size_t) = 0;
        // Verify if the specified player can receive a noble
        virtual void nobleVerification(size_t) = 0;
        // Verifiy if the player is too rich
        virtual void overflowVerification(size_t) = 0;
    };

    class TextualController : public Controller
    {
    private:
    public:
        TextualController() = default;
        void initiateGame();
        void printGame();
        bool hasWon(size_t);
        void launch();
        void playTurn(size_t);
        void nobleVerification(size_t);
        void overflowVerification(size_t);

        // Fonction d'actions
        bool buyReservedCard();
        bool buyBoardCard();
        bool reserveCenterCard();
        bool reserveDrawCard();
        bool takeTwoIdenticalToken();
        bool takeThreeDifferentToken();
    };
}

#endif