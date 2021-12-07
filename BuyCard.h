//
// Created by Cléa Bordeau on 01/12/2021.
//

#include "splendor.h"
#include "action.h"

//Reste a faire sur ce fichier : Definir les methodes privées; Definir les conditions
//Attention on peut acheter une carte reservée ou une carte sur le plateau

namespace Splendor {
    class BuyCard : public Action {
    private:
        const BaseCard card;

        //methodes appelées pour l'execution
        void BankUpdate(Board& b) const ; //redonne les token à la bank
        void PlayerTokenUpdate(Player& p) const; //enleve les token au joueur
        void PlayerCardUpdate(Player& p) const {}; //ajoute la carte aux cartes du joueur
        void BoardCardUpdate(Board& b) const {}; //Enleve la carte du plateau
        void PlayerVictoryPointsUpdate(Player& p) const {}; //Mise à jour du nombre de point de victoire du joueur

    public:
        BuyCard(const BaseCard c) : card(c) {};
        bool condition(Board& b,Player& p) const {}; //verifie que le joueur a bien les jetons necessaires pour acheter la carte

        void executer(Board& b,Player& p) {
                if (condition( b, p)){
                    BankUpdate(b);
                    PlayerTokenUpdate(p);
                    PlayerCardUpdate( p);
                    BoardCardUpdate( b);
                    PlayerVictoryPointsUpdate(p);
                }
        };
    };
}