#if !defined(PLAYER_H)
#define PLAYER_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "ResourceCard.h"
#include "NobleCard.h"
#include "Bank.h"

namespace Splendor
{

    class Player
    {
    private:
        const std::string name;
        Bank bank;

        std::vector<const ResourceCard *> ressource[3];
        std::vector<const NobleCard *> nobles;

        const ResourceCard *ReservedCards[3];

    public:
        Player(std::string s) : name(s)
        {
            for (size_t i = 0; i < 3; i++)
                ReservedCards[i] = nullptr;
        }

        ~Player() = default;

        //Action play(vector<Action> actions);
        Bank getBank() { return bank; }

        int TotalToken()
        {
            int FinalAmount = 0;
            for (int i = 0; i < 6; i++)
            {
                FinalAmount += getBank().amount((Token)i);
            }
            return FinalAmount;
        }

        std::string getName() { return name; }

        int *getBonuses();

        int getPoint();

        // CHANGER DANS ACTION
        void putReservedCard(const ResourceCard &card);

        const ResourceCard &takeReservedCard(size_t i);

        const ResourceCard &takeReservedCard(const ResourceCard &card);

        void putResourceCard(const ResourceCard &card);

        void putNobleCard(const NobleCard &card);

        std::vector<const ResourceCard *> getRessources(size_t i) const
        {
            return ressource[i];
        }

        std::vector<const NobleCard *> getNobles() const
        {
            return nobles;
        }

        const ResourceCard *getReservedCards(size_t i) const
        {
            return ReservedCards[i];
        }
    };
}

#endif