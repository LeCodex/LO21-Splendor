#ifndef VIEWGAME_H
#define VIEWGAME_H

#include <QWidget>
#include <QLayout>
#include "../game.h"
#include "viewboard.h"
#include "../View.h"
#include "viewplayer.h"

class ViewGame : public QWidget, public View
{
    Q_OBJECT
private:
    QVBoxLayout* playersLayout;
    QHBoxLayout* gameLayout;
    QHBoxLayout* infoLayout;
    QVBoxLayout* layer;

    QLabel* info;
    ViewBoard* board;
    std::vector<ViewPlayer*> viewPlayers;
public:
    // Might make it into a Singleton too
    ~ViewGame(){}
    void update();
    explicit ViewGame(QWidget* parent = nullptr);
    auto getPlayers() const { return viewPlayers; }
    auto getBoard() const { return board; }
    void setActivePlayer(size_t i);
};

#endif // VIEWGAME_H
