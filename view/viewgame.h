#ifndef VIEWGAME_H
#define VIEWGAME_H

#include <QWidget>
#include <QLayout>
#include "controller.h"
#include "viewboard.h"
#include "viewplayer.h"

class ViewGame : public QWidget
{
    Q_OBJECT
private:
    Splendor::Controller controller;
    QHBoxLayout* playersLayout;
    QVBoxLayout* globalLayout;
    ViewBoard* board;
    std::vector<ViewPlayer*> viewPlayers;
public:
    explicit ViewGame(QWidget* parent = nullptr);
    virtual ~ViewGame() {}
};

#endif // VIEWGAME_H
