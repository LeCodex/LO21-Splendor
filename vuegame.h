#ifndef VUEGAME_H
#define VUEGAME_H

#include <QWidget>
#include <QLayout>
#include "splendor.h"
#include "vueboard.h"

class VueGame : public QWidget
{
    Q_OBJECT
private:
    Splendor::Controller controller;
    VueBoard* board;
    QHBoxLayout* playersLayout;
    QVBoxLayout* globalLayout;
public:
    explicit VueGame(QWidget* parent = nullptr);
    virtual ~VueGame() {}
};

#endif // VUEGAME_H
