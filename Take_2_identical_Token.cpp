//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "Take_2_identical_Token.h"

bool Splendor::Take_2_identical_Token::condition(Board &b, Player &p) const {
    int FinalAmount = p.TotalToken() + 3;
    FinalAmount += 2;
    return ( (b.getBank().amount(color)>=2) && (FinalAmount <= 10) );
};