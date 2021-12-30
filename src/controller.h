#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Splendor.h"
#include "game.h"
#include <iostream>
#include "View.h"
#include "view/viewgame.h"
#include <QApplication>
#include <QTime>
#include <QMainWindow>

namespace Splendor
{
    template<class T = View>
    class Controller
    {
    protected:
        T* view = nullptr;
        size_t actual_player = 0;

        Controller() = default;
        virtual ~Controller(){
            if(view) delete view;
        }
         bool stopped = false;
    public:
        void launch(){
            initiateGame();

            while (!stopped)
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

            end();
        }

        virtual void initiateGame() = 0;
        virtual void playTurn(size_t) = 0;
        virtual void end() = 0;
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
        void end(){
        }

        // Fonction d'actions
        bool buyReservedCard();
        bool buyBoardCard();
        bool reserveCenterCard();
        bool reserveDrawCard();
        bool takeTwoIdenticalToken();
        bool takeThreeDifferentToken();
    };

    class QtController : public QMainWindow, public Controller<ViewGame>
    {
        Q_OBJECT
    private:
        explicit QtController(QWidget* parent = nullptr);
        void promptError(std::string);

        // Inner classes
        struct Handler
        {
            QtController *instance;
            Handler() : instance(nullptr) {}
            ~Handler() { delete instance; }
        };

        static Handler handler;
    protected:
        void closeEvent(QCloseEvent *event);
    public:    
        ~QtController(){}
        void initiateGame();
        void playTurn(size_t);
        void nobleVerification(size_t);
        void overflowVerification(size_t);
        void end(){
            qInfo() << "Thanks for playing!";

            deleteInstance();

            std::exit(0);
        }

        static auto &getInstance()
        {
            if (handler.instance == nullptr)
                handler.instance = new QtController();
            return *handler.instance;
        }

        // Singleton deleter
        static void deleteInstance()
        {
            delete handler.instance;
            handler.instance = nullptr;
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
