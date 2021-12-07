//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "BuyCard.h"

void Splendor::BuyCard:: BankUpdate(Board& b) const {
    for (int t=Red; t!=Gold; t++) {
        b.getBank().put((Token)t, card.getCost((Token)t));
        //On ajoute à la bank le prix en Red de la carte
    }
}

void Splendor::BuyCard::PlayerTokenUpdate(Player &p) const {
    for (int t=Red; t!=Gold; t++) {
        p.getBank().take((Token)Red,card.getCost((Token)Red));
        //On ajoute à la bank le prix en Red de la carte
    }
}