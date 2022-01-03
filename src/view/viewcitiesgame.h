#ifndef VIEWCITIESGAME_H
#define VIEWCITIESGAME_H

#include "viewgame.h"
#include "viewcitiesboard.h"

class ViewCitiesGame : public ViewGame
{
    Q_OBJECT
public:
    ViewCitiesGame(Splendor::CitiesGame* g, QWidget* parent=nullptr) : ViewGame(g, parent)
    {
        delete board;
        board = new ViewCitiesBoard(g->getBoard());
        board->initialize();
        gameLayout->addWidget(board);
    }
};

#endif // VIEWCITIESGAME_H
