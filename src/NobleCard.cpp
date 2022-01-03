#include "NobleCard.h"
#include "Player.h"

bool Splendor::NobleCard::canBeTakenBy(Player &p) const {
    int* bonuses = p.getBonuses();
    for (size_t t = White; t != Gold; t ++) {
        if (getCost((Token)t) > bonuses[t]) return false;
    }

    return true;
}
