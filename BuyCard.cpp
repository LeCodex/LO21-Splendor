//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "BuyCard.h"

void Splendor::BuyCard:: BankUpdate(Board& b) const {
    for (int t=Red; t!=Gold; t++) {
        b.getBank().put((Token)t, card.getCost((Token)t));
        //On ajoute à la bank le prix de la carte pour chaque jeton
    }
}

void Splendor::BuyCard:: PlayerTokenUpdate(Player &p) const {
    for (int t=Red; t!=Gold; t++) {
        p.getBank().take((Token)Red,card.getCost((Token)Red));
        //On retire au joueur le prix de la carte pour chaque jeton
    }
}

///A faire
void Splendor::BuyCard:: PlayerCardUpdate(Player& p) const { //Ajoute la carte aux cartes du joueur
    /*const auto c1 = dynamic_cast<const ResourceCard&>(card);
    if (c1) p.PutNobleCard(c1);
    const auto c2 = dynamic_cast<const NobleCard>(card);
    if (c2) p.PutResourceCard(c2);
     */
}

void Splendor::BuyCard:: ReservedCardUpdate(Player& p) const { //Retire la carte des cartes reservées du joueur
    p.TakeReservedCard(card);
}

///A faire
void Splendor::BuyCard:: BoardCardUpdate(Board& b) const {  //Enleve la carte du plateau et en rajoute une nouvelle

}

///A faire (ou pas)
void Splendor::BuyCard:: PlayerVictoryPointsUpdate(Player& p) const {}

///A faire
bool Splendor::BuyCard:: condition(Board& b,Player& p) const{
    //le cumulé de ses jetons sur les cartes ressources et de ses jetons doivent etre suffisant
    //la carte doit etre sur le plateau ou reservée (est vraiment necessaire de verifier cela ?)
return 1;
}