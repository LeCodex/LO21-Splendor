#include "Player.h"
#include "ResourceCard.h"

using namespace Splendor;

//getPoint calcule le nombre de points d'un joueur en additionnant les prestiges des cartes ressources
int Player::getPoint() {
    int result=0;
    for (size_t i =0; i<3; i++){
        for (auto& tmp : ressource[i]){
            result+=tmp->getPrestige();
        }
    }
    return result;
}

//getBonuses recupere tous les discounts des cartesRessources
int *Player::getBonuses() {
    int bonuses[5];
    for (auto i=0;i<3;i++){
        for (auto& tmp : ressource[i]){
            bonuses[tmp->getResource()]+=1;
        }
    }
    return bonuses;
}

void Player::putReservedCard(const ResourceCard &card){
    for (size_t i=0; i<3; i++) {
        if (ReservedCards[i] != nullptr) {
            ReservedCards[i] = card;
            return;
        }
    }
    throw "Po de place\n";
}

const ResourceCard& Player::takeReservedCard(size_t i){
        ReservedCards[i]=nullptr;
    }
const ResourceCard& Player::takeReservedCard(const ResourceCard& card) {
    for (size_t i = 0; i < 3; i++) {
        if (card==ReservedCards[i]) {ReservedCards[i]=nullptr; return card;}
    }
}

void Player::putResourceCard(const ResourceCard& card){
    int niveau = card.getLevel();
    ressource[i].pushback(card);
}

void Player::putNobleCard(const NobleCard& card){
    noble.pushback(card);
}