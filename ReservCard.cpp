//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "ReservCard.h"


void Splendor::ReservCard:: PlayerTokenUpdate(Player& p) const {
    p.getBank().put(Gold,1);
    //Ajout d'un jeton or apres chaque reservation
}

void Splendor::ReservCard:: BaseCardUpdate(Board& b, Player& p) const {

    p.PutReservedCard(card);
    //Ajout de la carte choisis au tableau de cartes reservées que possede le joueur

    b.removeCard(card);
    //Retire la carte du tableau
}

bool Splendor::ReservCard::condition(Board &b, Player &p) const {
    //Chaque joueur peu avoir au max 3 cartes reservées (fait)
    //Nb: faut il verifier que la carte est bien sur le plateau ? (pas fait)

    int nb = 0;
    for (auto i=0; i<=sizeof(p.getReservedCards()); i++){
        if(p.getReservedCards()[i] != nullptr) ++nb;
    }
    //Calcul du nombre de cartes déja reservées pour le joueur

    return (nb<=2);
    //Retourne 1 si il reste de la place, 0 si non
}