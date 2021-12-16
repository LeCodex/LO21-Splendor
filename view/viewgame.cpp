#include "viewgame.h"

ViewGame::ViewGame(Splendor::Game* g, QWidget* parent) : QWidget(parent), game(g)
{
    for (size_t i = 0; i < game->getNbPlayers(); i++) {
        ViewPlayer* v = new ViewPlayer(this);
        viewPlayers.push_back(v);
        // playersLayout->addWidget(v);
    }
}
