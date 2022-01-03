#ifndef VIEWCITIESGAME_H
#define VIEWCITIESGAME_H

#include "viewgame.h"
#include "viewcitiesboard.h"

class ViewCitiesGame : public ViewGame
{
    Q_OBJECT
protected:
    ViewCitiesBoard* board;
    Splendor::CitiesGame* game;
public:
    ViewCitiesGame(Splendor::CitiesGame* g, QWidget* parent=nullptr) : ViewGame(g, parent)
    {
        board = new ViewCitiesBoard(game->getBoard());
    }
};

#endif // VIEWCITIESGAME_H
