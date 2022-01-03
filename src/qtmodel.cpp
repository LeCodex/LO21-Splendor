#include "model.h"
#include "qtcontroller.h"

Splendor::QtModel::QtModel(QWidget *parent) : QMainWindow(parent) {}

void Splendor::QtModel::initiateGame()
{

    // Create an instance of nb player
    Splendor::Game &g = Splendor::Game::createInstance(Splendor::QtController::getInstance().getNb());

    // Add the players
    for (size_t i = 0; i < Splendor::QtController::getInstance().getNb(); i++)
        g.addPlayer(Splendor::QtController::getInstance().getPlayerNames()[i]->text().toStdString(), Splendor::QtController::getInstance().getAi()[i]->checkState(), i);

    view = new ViewGame(&g, this);

    // Après avoir initalisé le jeu, l'ajoute a la fenêtre
    setCentralWidget(view);

    show();
}

bool actionPerformed = false;

void Splendor::QtModel::playTurn(size_t)
{
    view->update();
    view->getInfo()->setText("Cliquez sur les jetons ou cartes du plateau pour effectuer des actions");

    qInfo() << "Waiting for player action...";
    view->setActivePlayer(currentPlayer);
    tokenSelection.clear();
    phase = Phase::Play;

    Game& game = getGameInstance();
    Splendor::Player& player = game.getPlayer(currentPlayer);

    if (player.isAI()) {
        game.playAI(player, 1);
    } else {
        // While no action has been performed, just wait for one
        while (!actionPerformed && !this->stopped) {
            QApplication::processEvents();
        }
    }

    if(this->stopped) return;

    // Hiding the hand in case it isn't
    view->getPlayers()[currentPlayer]->getHand()->hide();

    qInfo() << "Action performed!";

    actionPerformed = false;
}

// Verify if the specified player can receive a noble
void Splendor::QtModel::nobleVerification(size_t) {
    qInfo() << "Noble verification";
    view->update();

    Splendor::Game& game = getGameInstance();
    Splendor::Player& player = game.getPlayer(currentPlayer);

    phase = Phase::Nobles;

    vector<const Splendor::NobleCard*> nobles;
    for (auto noble : game.getBoard().getNobles()) {
        if (noble->canBeTakenBy(player)) nobles.push_back(noble);
    }
    // qInfo() << nobles.size();

    if (nobles.size() == 1) {
        game.chooseNoble(*nobles[0], player);
        promptError("Vous avez reçu un noble!");
    } else if (nobles.size() > 1) {
        // Disable nobles that can't be picked
        for (auto viewNoble : view->getBoard()->getNobleCards()) {
            viewNoble->setDisabled(true);

            for (auto noble : nobles) {
                if (noble == viewNoble->getCard()) {
                    viewNoble->setDisabled(false);
                    break;
                }
            }
        }

        if (player.isAI()) {
            game.chooseNoble(*nobles[0], player);
            promptError("Vous avez reçu un noble!");
        } else {
            view->getInfo()->setText("Choississez un noble à prendre");
            promptError("Veuillez choisir un noble à recevoir");

            // Wait for the player to choose a noble
            while (!actionPerformed && !this->stopped){
                QApplication::processEvents();
            }
        }
    } // Else do nothing

    for (auto viewNoble : view->getBoard()->getNobleCards()) {
        viewNoble->setDisabled(false);
    }

    actionPerformed = false;
}

// Verifiy if the player is too rich
void Splendor::QtModel::overflowVerification(size_t) {
    qInfo() << "Overflow verification";

    Splendor::Game& game = getGameInstance();
    Splendor::Player& player = game.getPlayer(currentPlayer);

    phase = Phase::Overflow;

    if (player.TotalToken() > 10 && !player.isAI()) {
        promptError("Veuillez choisir des jetons à rendre");
        view->getInfo()->setText("Vous avez trop de jetons! Choississez en à rendre");
    }

    while (player.TotalToken() > 10) {
        if (player.isAI()) {
            game.returnTokenAI(player);
        } else {
            view->update();

            // Wait for the player to remove tokens
            while (!actionPerformed && !this->stopped){
                QApplication::processEvents();
            }
        }

        actionPerformed = false;
    }
}

bool Splendor::QtModel::buyReservedCard(Splendor::ResourceCard *c)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.buyReservedCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible d'acheter la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::buyBoardCard(Splendor::ResourceCard *c)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.buyBoardCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible d'acheter la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::reserveCenterCard(Splendor::ResourceCard *c)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.reserveCenterCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible de reserver la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::reserveDrawCard(size_t i)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.reserveDrawCard(i, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible de reserver la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::takeToken(Splendor::Token t)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    tokenSelection.push_back(t);

    bool cont = true;
    if (tokenSelection.size() == 2 && tokenSelection[0] == tokenSelection[1]) {
        actionPerformed = g.takeTwoIdenticalToken(tokenSelection[0], p);
    } else if (tokenSelection.size() == 3) {
        actionPerformed = g.takeThreeDifferentToken(tokenSelection[0], tokenSelection[1], tokenSelection[2], p);
    } else {
        cont = false;
    }

    if (cont) {
        tokenSelection.clear();

        if (!actionPerformed)
            promptError("Impossible de prendre les jetons demandés");
    }

    return actionPerformed;
}

bool Splendor::QtModel::returnToken(Splendor::Token t)
{
    if (phase != Phase::Overflow) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    actionPerformed = g.returnToken(t, p);

    if (!actionPerformed)
        promptError("Impossible de rendre le jeton");

    return actionPerformed;
}

bool Splendor::QtModel::chooseNoble(Splendor::NobleCard *c)
{
    if (phase != Phase::Nobles) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    actionPerformed = g.chooseNoble(*c, p);

    if (!actionPerformed)
        promptError("Impossible de choisir ce noble");

    return actionPerformed;
}

void Splendor::QtModel::promptError(std::string s)
{
    QMessageBox message;

    message.setIcon(QMessageBox::Icon::Information);
    message.setText(QString::fromStdString(s));

    message.exec();
}

void Splendor::QtModel::closeEvent(QCloseEvent *event)
{
    this->stopped = true;

    QMainWindow::closeEvent(event);
}
