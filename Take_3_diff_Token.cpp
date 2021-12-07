//
// Created by Cléa Bordeau on 01/12/2021.
//

#include "Take_3_diff_Token.h"

bool Splendor::Take_3_diff_Token::condition(Board &b, Player &p) const { //la banque doit avoir assez de jeton et un joueur ne doit jamais avoir plus de 10 jetons à la fin de son tour
    int FinalAmount = p.TotalToken() + 3;
    return ((b.getBank().amount(color1)>=1) && (b.getBank().amount(color2)>=1) && (b.getBank().amount(color3)>=1)
            && (FinalAmount <=10));
}