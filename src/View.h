#ifndef VIEW_H
#define VIEW_H

#include "Splendor.h"

class View
{
private:
    Splendor::Game* game;
public:
    View(Splendor::Game *g): game(g){}
    virtual ~View(){}
    virtual void update() = 0;
    Splendor::Game& getGame(){ return *game; }
};

class TextualView : public View {
public:
    ~TextualView(){}
    virtual void update(){
    }
};

#endif // VIEW_H
