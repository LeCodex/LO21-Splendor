#include "Player.h"

int Splendor::CitiesPlayer::getScore() const {
    int result = 0;

    for (size_t i = 0; i < 3; i++)
    {
        for (auto &tmp : getResources(i))
        {
            result += tmp->getPrestige();
        }
    }

    return result;
}
