#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Splendor.h"
#include "game.h"
#include <iostream>
#include "View.h"
#include "view/viewgame.h"
#include <QApplication>
#include <QTime>

namespace Splendor
{
    template<class T = View>
    class Controller
    {
    protected:
        T* view = nullptr;
        size_t actual_player = 0;

        Controller() = default;
        virtual ~Controller(){ if(view) delete view; }

    public:
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
        #define WINNING_POINTS 15
        bool hasWon(size_t i){
            Player &p = Game::getInstance().getPlayer(i);

            int points = p.getPoint();

            return points >= WINNING_POINTS;
        }
        // Verify if the specified player can receive a noble
        virtual void nobleVerification(size_t) = 0;
        // Verifiy if the player is too rich
        virtual void overflowVerification(size_t) = 0;
    };

    class TextualController : public Controller<TextualView>
    {
    private:
    public:
        TextualController() = default;
        void initiateGame();
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

    class QtController : public QWidget, public Controller<ViewGame>
    {
        Q_OBJECT
    private:
        explicit QtController(QWidget* parent = nullptr);
        void promptError(std::string);
    public:
        void initiateGame();
        void playTurn(size_t);
        void nobleVerification(size_t);
        void overflowVerification(size_t);

        static auto &getInstance()
        {
            static QtController c;
            return c;
        }

        // Fonction d'actions
        bool buyReservedCard(Splendor::ResourceCard* c);
        bool buyBoardCard(Splendor::ResourceCard* c);
        bool reserveCenterCard(Splendor::ResourceCard* c);
        bool reserveDrawCard(size_t i);
        bool takeTwoIdenticalToken();
        bool takeThreeDifferentToken();
    };
}

#endif
