//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "splendor.h"
#include "action.h"

//Reste a faire sur ce fichier : Definir les conditions

namespace Splendor {
    class ReservCard : public Action {
    private:
        const BaseCard card;

        //methode appelée pour l'execution
        void BaseCardUpdate(Board& b, Player& p) const;
        //Cette fonction va permettre de reserver une carte pour le tour d'apres

        void PlayerTokenUpdate(Player& p) const;
        //ajoute un jeton or au joueur

    public:
        ReservCard(const BaseCard c ) : card(c){};

        bool condition(Board& b,Player& p) const;

        void executer(Board& b,Player& p) {
            if (condition(b, p)) {
                BaseCardUpdate(b,p);
                PlayerTokenUpdate(p);
            }
        };
    };
}