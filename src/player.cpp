#include "player.h"

int Player::getPoint() {
    int result=0;
    for (auto i=0;i<3;i++){
        result+=getRessourceCard(i).prestige;
    }
    return result;
}

int *Player::getBonuses() {
    int bonuses[5];
    for (auto i=0;i<3;i++){
        for (auto j=0;j<5;j++){
        bonuses[j]+=getRessourceCard(i).cost[j];
    }
    return bonuses;
}

