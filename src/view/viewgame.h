#ifndef VIEWGAME_H
#define VIEWGAME_H

#include <QWidget>
#include <QLayout>
#include "../controller.h"
#include "viewboard.h"
#include "viewplayer.h"

class ViewGame : public QWidget
{
    Q_OBJECT
private:
    Splendor::Game* game;
    Splendor::Controller* controller; // Might not be necessary if the Controller is a Singleton

    QVBoxLayout* playersLayout;
    QHBoxLayout* gameLayout;
    QHBoxLayout* infoLayout;
    QVBoxLayout* layer;

    QLabel* info;
    ViewBoard* board;
    std::vector<ViewPlayer*> viewPlayers;
public:
    // Might make it into a Singleton too
    explicit ViewGame(Splendor::Game* g, QWidget* parent = nullptr);
    auto getPlayers() const { return viewPlayers; }
    auto getBoard() const { return board; }

    void setInfo(std::string i) { info->setText(i.c_str()); }
};

#endif // VIEWGAME_H
