#include "viewgame.h"

ViewGame::ViewGame(QWidget* parent) : QWidget(parent)
{
<<<<<<< HEAD
    Splendor::Game &g = Splendor::Game::getInstance();
    playersLayout = new QVBoxLayout();
    for (size_t i = 0; i < g.getNbPlayer(); i++) {
        ViewPlayer* v = new ViewPlayer(&g.getPlayer(i), this);
=======
    playersLayout = new QVBoxLayout();
    for (size_t i = 0; i < game->getNbPlayer(); i++) {
        ViewPlayer* v = new ViewPlayer(new Splendor::Player(game->getPlayer(i).getName()), this);
>>>>>>> aa3162cceede6de81b3e53d417e0c57a94036783
        viewPlayers.push_back(v);
        playersLayout->addWidget(v);
    }

    setActivePlayer(0);

    gameLayout = new QHBoxLayout();
    board = new ViewBoard(g.getBoard());
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

<<<<<<< HEAD
void ViewGame::setActivePlayer(size_t i){
    for(size_t k = 0; k < Splendor::Game::getInstance().getNbPlayer(); k++)
        viewPlayers[k]->setAsCurrent(false);
    viewPlayers[i]->setAsCurrent(true);
}

void ViewGame::update(){
    board->updateCards();
    for(size_t i = 0; i < Splendor::Game::getInstance().getNbPlayer(); i++){
        viewPlayers[i]->updateCards();
        viewPlayers[i]->updateTokens();
    }
=======
ViewGame::~ViewGame() {
    delete playersLayout;
    delete gameLayout;
    delete infoLayout;
    delete layer;
>>>>>>> aa3162cceede6de81b3e53d417e0c57a94036783
}
