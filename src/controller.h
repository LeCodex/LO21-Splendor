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
#include <QWidget>
#include <QMessageBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QCheckBox>

class View;

namespace Splendor
{
    template<class T>
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

        virtual Game& getGameInstance() = 0;

        virtual void launch(){
            initiateGame();

            int lastIndex = -1;
            while (!stopped)
            {
                // End of the game
                if (lastIndex == currentPlayer) {
                    view->update();

                    int winner = 0, maxScore = 0;
                    Game& game = getGameInstance();

                    for (size_t i = 0; i < game.getNbPlayer(); i++) {
                        if (game.getPlayer(i).getScore() > maxScore) {
                            maxScore = game.getPlayer(i).getScore();
                            winner = i;
                        }
                    }

                    std::stringstream s;
                    s << "Victoire du joueur " << winner + 1 << ", " << game.getPlayer(winner).getName() << "!";
                    promptError(s.str());
                    break;
                }

                // Turn proper
                playTurn(currentPlayer);

                // Overflow of token verification
                overflowVerification(currentPlayer);

                // Noble verification
                nobleVerification(currentPlayer);

                // End game verification
                if (hasWon(currentPlayer) && lastIndex == -1) {
                    view->update();

                    std::stringstream s;
                    s << "Le joueur " << currentPlayer + 1 << ", " << getGameInstance().getPlayer(currentPlayer).getName() << " a atteint 15 points. DERNIER TOUR!";
                    promptError(s.str());

                    lastIndex = currentPlayer;
                }

                // Incrementation
                currentPlayer = (currentPlayer + 1) % getGameInstance().getNbPlayer();
            }

            end();
        }

        virtual void initiateGame() = 0;
        virtual void playTurn(size_t) = 0;
        virtual void end() = 0;
        // Verifiy if the specified player has won
        #define WINNING_POINTS 15
        bool hasWon(size_t i){
            Player &p = getGameInstance().getPlayer(i);

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

    class QtController :  public QMainWindow, public Controller<ViewGame>
    {
        Q_OBJECT
        friend class Singleton<QtController>;
    private:
        struct Handler
        {
            QtController *instance;
            Handler() : instance(nullptr) {}
            ~Handler() { delete instance; }
        };

        static Handler handler;
    protected:
        explicit QtController(QWidget* parent = nullptr);

        vector<Token> tokenSelection;

        enum Phase{
            Play,
            Overflow,
            Nobles
        };

        Phase phase;

        void closeEvent(QCloseEvent *event) override;
    public:
        static QtController &getInstance()
        {
            if (handler.instance == nullptr)
                handler.instance = new QtController();
            return *handler.instance;
        }

        virtual ~QtController() override {}
        virtual void initiateGame() override;
        virtual void playTurn(size_t) override;
        virtual void nobleVerification(size_t) override;
        virtual void overflowVerification(size_t) override;
        virtual void end() override {
            qInfo() << "Thanks for playing!";
            std::exit(0);
        }
        virtual Game& getGameInstance() override{ return Splendor::Game::getInstance(); }
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

    class StrongHoldQtController : public QtController{
        private:
            struct Handler
            {
                StrongHoldQtController *instance;
                Handler() : instance(nullptr) {}
                ~Handler() { delete instance; }
            };

            static Handler handler;

            explicit StrongHoldQtController(QWidget* parent = nullptr): QtController(parent){}
        public:

            static StrongHoldQtController &getInstance()
            {
                if (handler.instance == nullptr)
                    handler.instance = new StrongHoldQtController();
                return *handler.instance;
            }

            ~StrongHoldQtController() override = default;
            virtual void initiateGame() override;
            Game& getGameInstance() override { return StrongHoldGame::getInstance(); }
    };

}

#endif
