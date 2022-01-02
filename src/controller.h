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
        size_t currentPlayer = 0;

        Controller(){}
        virtual ~Controller(){
            if(view) delete view;
        }

        bool stopped = false;
    public:
        Controller(const Controller&) = delete;
        Controller& operator==(const Controller&) = delete;

        void launch(){
            initiateGame();

            while (!stopped)
            {
                playTurn(currentPlayer);

                // Overflow of token verification
                overflowVerification(currentPlayer);

                // Noble verification
                nobleVerification(currentPlayer);

                // End game verification
                if (hasWon(currentPlayer)) {
                    std::stringstream s;
                    s << "Victoire du joueur " << currentPlayer + 1 << ", " << Game::getInstance().getPlayer(currentPlayer).getName() << "!";
                    promptError(s.str());
                    break;
                }

                // Incrementation
                currentPlayer = (currentPlayer + 1) % Game::getInstance().getNbPlayer();
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

            int points = p.getScore();

            return points >= WINNING_POINTS;
        }
        // Verify if the specified player can receive a noble
        virtual void nobleVerification(size_t) = 0;
        // Verifiy if the player is too rich
        virtual void overflowVerification(size_t) = 0;
        virtual void promptError(std::string) = 0;
    };

    /*
    class TextualController : public Controller<TextualView>
    {
    protected:
        void promptError(std::string s) override { std::cout << s; }
    public:
        TextualController() = default;
        void initiateGame() override;
        void playTurn(size_t) override;
        void nobleVerification(size_t) override;
        void overflowVerification(size_t) override;
        void end() override{}

        // Fonction d'actions
        bool buyReservedCard();
        bool buyBoardCard();
        bool reserveCenterCard();
        bool reserveDrawCard();
        bool takeTwoIdenticalToken();
        bool takeThreeDifferentToken();
    };
    */

    template<typename T>
    class Singleton
    {
    protected:
        Singleton() noexcept = default;

        Singleton(const Singleton&) = delete;

        Singleton& operator=(const Singleton&) = delete;

        virtual ~Singleton() = default;

    public:
        static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
        {
            static T instance{};
            return instance;
        }
    };

    class QtController :  public QMainWindow, public Singleton<QtController>, public Controller<ViewGame>
    {
        Q_OBJECT
        friend class Singleton<QtController>;
    private:
        explicit QtController(QWidget* parent = nullptr);
        vector<Token> tokenSelection;

        enum Phase {
            Play,
            Overflow,
            Nobles
        };
        Phase phase;
    protected:
        void closeEvent(QCloseEvent *event) override;
    public:
        ~QtController() override {}
        void initiateGame() override;
        void playTurn(size_t) override;
        void nobleVerification(size_t) override;
        void overflowVerification(size_t) override;
        void end() override {
            qInfo() << "Thanks for playing!";
            std::exit(0);
        }
        void promptError(std::string) override;

        const vector<Token>& getTokenSelection() { return tokenSelection; }

        // Fonction d'actions
        bool buyReservedCard(Splendor::ResourceCard* c);
        bool buyBoardCard(Splendor::ResourceCard* c);
        bool reserveCenterCard(Splendor::ResourceCard* c);
        bool reserveDrawCard(size_t i);
        bool takeToken(Splendor::Token t);
        bool returnToken(Splendor::Token t);
        bool chooseNoble(Splendor::NobleCard* c);
    };

   }

#endif
