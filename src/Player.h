#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "ResourceCard.h"
#include "NobleCard.h"
#include "Bank.h"

#include <QDebug>

namespace Splendor
{
    class Player
    {
    private:
        const std::string name;
        Bank bank;

        std::vector<const ResourceCard*> ressource[3];
        std::vector<const NobleCard*> nobles;

        const ResourceCard *ReservedCards[3];
        bool AI;
    public:
        Player(std::string s, bool ai) : name(s), AI(ai)
        {
            for (size_t i = 0; i < 3; i++)
                ReservedCards[i] = nullptr;
        }

        virtual ~Player() = default;

        //Action play(vector<Action> actions);
        Bank& getBank() { return bank; }
        const Bank& getBank() const { return bank; }

        int TotalToken() const
        {
            int FinalAmount = 0;
            for (int i = 0; i < 6; i++)
            {
                FinalAmount += getBank().amount((Token)i);
            }
            return FinalAmount;
        }

        const std::string& getName() const { return name; }

        bool isAI() const { return AI; }

        int *getBonuses() const;

        virtual int getScore() const;

        void putReservedCard(const ResourceCard &card);

        const ResourceCard &takeReservedCard(size_t i);

        const ResourceCard &takeReservedCard(const ResourceCard &card);

        void putResourceCard(const ResourceCard &card);

        void putNobleCard(const NobleCard &card);

        std::vector<const ResourceCard *> getResources(size_t i) const
        {
            return ressource[i];
        }

        std::vector<const NobleCard *> getNobles() const
        {
            return nobles;
        }

        const ResourceCard* getReservedCard(size_t i) const
        {
            return ReservedCards[i];
        }
    };

    class CitiesPlayer : public Player
    {
    public:
        CitiesPlayer(std::string s, bool ai): Player(s, ai) {}

        int getScore() const override;
    };
}

#endif // PLAYER_H
