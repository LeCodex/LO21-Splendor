#include "NobleCard.h"

bool Splendor::NobleCard::canBeTakenBy(Splendor::Player &p) {
    int* bonuses = p.getBonuses();
    for (size_t t = White; t != Gold; t ++) {
        if (getCost((Token)t) > bonuses[t]) return false;
    }

    return true;
}
