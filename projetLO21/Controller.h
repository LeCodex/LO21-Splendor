//
// Created by Cléa Bordeau on 24/12/2021.
//

#ifndef PROJETLO21_CONTROLLER_H
#define PROJETLO21_CONTROLLER_H
#include "splendor.h"
#include "Board.h"
#include "Player.h"

namespace Splendor {
    class Controller{
    private :
        bool conditionBuyCard(Board& b,Player& p,BaseCard card); //Retourne la condition pour BuyReservedCard et BuyBoardCard
        int real_cost(Player& p,BaseCard card, Token t); //Retourne cout réél pour un jeton qu'un joueur doit payer pour acheter une carte en prenant en compte la reduction avec ses cartes resssources

    public:
        bool BuyReservedCard(BaseCard card , Board& b, Player& p); //Le joueur p achete une carte qu'il a deja reservée
        bool BuyBoardCard(BaseCard card, Board& b, Player& p); //Le joueur p achete une carte du plateau
        bool ReservCard(BaseCard card, Board& b, Player& p); //Le joueur reserve une carte
        bool Take_2_identical_Token(Token color, Board& b, Player& p) ; //Le joueur prend 2 jetons identiques
        bool Take_3_diff_Token(Token color1, Token color2, Token color3, Board& b, Player& p); //Le joureur prend 3 jetons diffèrents
    };

}
#endif //PROJETLO21_CONTROLLER_H
