#ifndef MODEL_H
#define MODEL_H

#include "Splendor.h"
#include "game.h"
#include <iostream>
#include "View.h"
#include "view/viewgame.h"
#include "view/viewcitiesgame.h"
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
    class Model
    {
    protected:
        T* view = nullptr;
        size_t currentPlayer = 0;

        bool stopped = false;
    public:
        Model(){}
        virtual ~Model(){
            if (view) delete view;
        }

        virtual Game& getGameInstance() = 0;

        virtual void launch(){
            initiateGame();

            int lastIndex = -1;
            while (!stopped)
            {
                // End of the game
                if (lastIndex == currentPlayer) {
                    view->update();

                    int winner = 0;
                    Game& game = getGameInstance();

                    for (size_t i = 0; i < game.getNbPlayer(); i++) {
                        if (winCondition(i, winner)) {
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
                if (endCondition(currentPlayer) && lastIndex == -1) {
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
        virtual bool endCondition(size_t i){
            Player &p = getGameInstance().getPlayer(i);

            int points = p.getScore();

            return points >= WINNING_POINTS;
        }
        virtual bool winCondition(size_t i, size_t winner){
            Player &p = getGameInstance().getPlayer(i);
            Player &w = getGameInstance().getPlayer(winner);

            int totalResourcesP = 0;
            int totalResourcesW = 0;
            for (size_t i = 0; i < 3; i++) {
                totalResourcesP += p.getRessources(i).size();
                totalResourcesW += w.getRessources(i).size();
            }

            return p.getScore() > w.getScore() || totalResourcesP < totalResourcesW;
        }
        // Verify if the specified player can receive a noble
        virtual void nobleVerification(size_t) = 0;
        // Verifiy if the player is too rich
        virtual void overflowVerification(size_t) = 0;
        virtual void promptError(std::string) = 0;
    };

    /*
    class TextualModel : public Model<TextualView>
    {
    protected:
        void promptError(std::string s) override { std::cout << s; }
    public:
        TextualModel() = default;
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

    class QtModel : public QMainWindow, public Model<ViewGame>
    {
        Q_OBJECT
    protected:
        vector<Token> tokenSelection;

        enum Phase{
            Play,
            Overflow,
            Nobles
        };
        Phase phase;

        void closeEvent(QCloseEvent *event) override;
    public:
        explicit QtModel(QWidget* parent = nullptr);
        virtual ~QtModel() override {}
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

    class CitiesQtModel : public QtModel
    {
    public:
        explicit CitiesQtModel(QWidget* parent = nullptr): QtModel(parent){}

        ~CitiesQtModel() override = default;
        virtual void initiateGame() override;
        Game& getGameInstance() override { return CitiesGame::getInstance(); }

        bool endCondition(size_t i) override
        {
            Player &p = getGameInstance().getPlayer(i);

            return p.getNobles().size() > 1;
        }

        bool winCondition(size_t i, size_t winner) override
        {
            Player &p = getGameInstance().getPlayer(i);
            Player &w = getGameInstance().getPlayer(winner);

            return p.getNobles().size() > w.getNobles().size() || QtModel::winCondition(i, winner);
        }
    };

}

#endif
