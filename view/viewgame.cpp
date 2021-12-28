#include "viewgame.h"

ViewGame::ViewGame(Splendor::Game* g, QWidget* parent) : QWidget(parent), game(g)
{
    playersLayout = new QVBoxLayout();
    for (size_t i = 0; i < game->getNbPlayers(); i++) {
        ViewPlayer* v = new ViewPlayer(new Splendor::Player("Bob"), this);
        viewPlayers.push_back(v);
        playersLayout->addWidget(v);
    }
    viewPlayers[0]->setAsCurrent(true);

    gameLayout = new QHBoxLayout();
    board = new ViewBoard(*new Splendor::Board());
    gameLayout->addLayout(playersLayout);
    gameLayout->addWidget(board);

    infoLayout = new QHBoxLayout();
    info = new QLabel();
    info->setText("Bienvenue dans Splendor!");
    infoLayout->addWidget(info);

    layer = new QVBoxLayout();
    layer->addLayout(infoLayout);
    layer->addLayout(gameLayout);

    setLayout(layer);
}
