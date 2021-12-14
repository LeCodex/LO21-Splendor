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
    Splendor::Controller* controller; // Might not be necessary if the Controller is a Singleton
    QHBoxLayout* playersLayout;
    QVBoxLayout* globalLayout;
    ViewBoard* board;
    std::vector<ViewPlayer*> viewPlayers;
public:
    // Might make it into a Singleton too
    explicit ViewGame(QWidget* parent = nullptr);
};

#endif // VIEWGAME_H
