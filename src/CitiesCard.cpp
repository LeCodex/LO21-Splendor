#include"NobleCard.h"
#include "Player.h"

bool Splendor::CitiesCard::canBeTakenBy(Player &p) const {
    if (p.getScore() < getPrestige()) return false;

    int* bonuses = p.getBonuses();
    for (size_t t = White; t != Gold; t ++) {
        if (getCost((Token)t) > bonuses[t]) return false;
    }

    if (otherCost == 0) return true;
    for (size_t t = White; t != Gold; t ++) {
        if (bonuses[t] >= otherCost && getCost((Token)t) == 0) return true;
    }

    return false;
}
