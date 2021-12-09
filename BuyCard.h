//
// Created by Cléa Bordeau on 01/12/2021.
//

#include "splendor.h"
#include "action.h"

///Reste a faire sur ce fichier : Definir les methodes privées; Definir les conditions
///Attention on peut acheter une carte reservée ou une carte sur le plateau
///Demander pour l'attribut Reserved si c'est une bonne idee de faire comme ca

namespace Splendor {

    class BuyCard : public Action {

    private:

        //Attributs
        const BaseCard card;
        bool Reserved;

        //Methodes appelées pour l'execution
        void BankUpdate(Board& b) const ; //Redonne les token à la bank
        void PlayerTokenUpdate(Player& p) const; //Enleve les token au joueur
        void PlayerCardUpdate(Player& p) const ;//Ajoute la carte aux cartes du joueur
        void ReservedCardUpdate(Player& p) const ; //Retire la carte des cartes reservées du joueur
        void BoardCardUpdate(Board& b) const ; //Enleve la carte du plateau et en rajoute une nouvelle
        void PlayerVictoryPointsUpdate(Player& p) const ; //Mise à jour du nombre de point de prestige du joueur

    public:

        BuyCard(const BaseCard c) : card(c) {}; ///Revoir pour ajouter reserved
        bool condition(Board& b,Player& p) const override; //verifie que le joueur a bien les jetons necessaires pour acheter la carte

        void executer(Board& b,Player& p) override {
                if (condition( b, p)){

                    BankUpdate(b);
                    PlayerTokenUpdate(p);
                    PlayerCardUpdate( p);
                    PlayerVictoryPointsUpdate(p);
                    if (Reserved == 1) ReservedCardUpdate(p);
                    else BoardCardUpdate( b);
                }
        };
    };
}
