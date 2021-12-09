//
// Created by Cléa Bordeau on 01/12/2021.
//

#include "splendor.h"
#include "Board.h"
#include "Player.h"

//Reste a faire sur ce fichier :

namespace Splendor {
    class Action {
    public:
        virtual bool condition(Board& b,Player& p) const = 0; //qui sera définit differement pour chaque sous classe
        virtual void executer(Board& b,Player& p) = 0; //idem
    };
}
