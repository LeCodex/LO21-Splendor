#ifndef VIEWGAME_H
#define VIEWGAME_H

#include <QWidget>
#include <QLayout>
#include "../game.h"
#include "viewboard.h"
#include "../View.h"
#include "viewplayer.h"
#include <QCloseEvent>

class ViewGame : public QWidget, public View
{
    Q_OBJECT
private:
    QVBoxLayout *playersLayout;
    QHBoxLayout *gameLayout;
    QHBoxLayout *infoLayout;
    QVBoxLayout *layer;

    QLabel *info;
    ViewBoard *board;
    std::vector<ViewPlayer *> viewPlayers;
public:
    // Might make it into a Singleton too
    ~ViewGame();

    virtual void update();
    explicit ViewGame(Splendor::Game*, QWidget *parent = nullptr);
    auto getPlayers() const { return viewPlayers; }
    auto getBoard() const { return board; }
    auto getInfo() const { return info; }
    void setActivePlayer(size_t i);
};


#endif // VIEWGAME_H
