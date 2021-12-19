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
    };

    class TextualController : public Controller
    {
    private:
    public:
        void initiateGame();
        void printGame();
        void launch();
    };
}

#endif