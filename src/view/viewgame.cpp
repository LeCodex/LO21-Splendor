#include "viewgame.h"
#include "../model.h"

ViewGame::ViewGame(Splendor::Game* _g, QWidget* parent) : QWidget(parent), View(_g)
{
    Splendor::Game &g = *getGame();
    playersLayout = new QVBoxLayout();
    for (size_t i = 0; i < g.getNbPlayer(); i++) {
        ViewPlayer* v = new ViewPlayer(&g.getPlayer(i), this);
        viewPlayers.push_back(v);
        playersLayout->addWidget(v);
    }

    setActivePlayer(0);

    gameLayout = new QHBoxLayout();
    board = new ViewBoard(g.getBoard());
    board->initialize();
    gameLayout->addLayout(playersLayout);
    gameLayout->addWidget(board);

    infoLayout = new QHBoxLayout();
    info = new QLabel();
    infoLayout->addWidget(info);

    layer = new QVBoxLayout();
    layer->addLayout(infoLayout);
    layer->addLayout(gameLayout);

    setLayout(layer);
}

void ViewGame::setActivePlayer(size_t i){
    for(size_t k = 0; k < getGame()->getNbPlayer(); k++)
        viewPlayers[k]->setAsCurrent(false);
    viewPlayers[i]->setAsCurrent(true);
}

void ViewGame::update(){
    board->updateCards();
    board->updateTokens();

    for(size_t i = 0; i < getGame()->getNbPlayer(); i++){
        viewPlayers[i]->updateCards();
        viewPlayers[i]->updateTokens();
    }
}

ViewGame::~ViewGame() {
    delete playersLayout;
    delete gameLayout;
    delete infoLayout;
    delete layer;
}
