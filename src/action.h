#ifndef ACTION_H
#define ACTION_H

#include "Splendor.h"
#include "board.h"
#include "Player.h"

//Reste a faire sur ce fichier :

namespace Splendor
{
    class Action
    {
    public:
        virtual bool condition(Board &b, Player &p) const = 0; //qui sera définit differement pour chaque sous classe
        virtual void executer(Board &b, Player &p) = 0;        //idem
    };
}

#endif