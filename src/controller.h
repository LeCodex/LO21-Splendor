#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Splendor.h"
#include "game.h"
#include <iostream>
#include "View.h"

namespace Splendor
{
    class Controller
    {
    protected:
        View* view;
        size_t actual_player = 0;

    public:
        Controller() = default;

        void launch(){
            initiateGame();

            while (true)
            {
                view->update();

                playTurn(actual_player);

                // Overflow of token verification
                overflowVerification(actual_player);

                // Noble verification
                nobleVerification(actual_player);

                // End game verification
                if (hasWon(actual_player))
                    break;

                // Incrementation
                actual_player = (actual_player + 1) % Game::getInstance().getNbPlayer();
            }
        }
        virtual void initiateGame() = 0;
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
