#ifndef VUEGAME_H
#define VUEGAME_H

#include <QWidget>
#include <QLayout>
#include "controller.h"
#include "vueboard.h"
#include "vueplayer.h"

class VueGame : public QWidget
{
    Q_OBJECT
private:
    Splendor::Controller controller;
    QHBoxLayout* playersLayout;
    QVBoxLayout* globalLayout;
    VueBoard* board;
    std::vector<VuePlayer*> vuePlayers;
public:
    explicit VueGame(QWidget* parent = nullptr);
    virtual ~VueGame() {}
};

#endif // VUEGAME_H
