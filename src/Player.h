#if !defined(PLAYER_H)
#define PLAYER_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "ResourceCard.h"
#include "NobleCard.h"
#include "Bank.h"

namespace Splendor {

    class Player {
    private:
        const std::string name;
        Bank bank;
        const std::vector<ResourceCard *> ressource[3];
        const std::vector<NobleCard *> nobles;

        const ResourceCard *ReservedCards[3];
    public:
        Player(std::string s) : name(s) {}

        ~Player();

        //Action play(vector<Action> actions);
        Bank getBank() { return bank; }

        int TotalToken() {
            int FinalAmount = 0;
            for (int i = 0; i < 6; i++) {
                FinalAmount += getBank().amount((Token) i);
            }
            return FinalAmount;
        }

        std::string getName() { return name; }

        int *getBonuses();

        int getPoint();

        // CHANGER DANS ACTION
        void putReservedCard(const ResourceCard &card);

        const ResourceCard& takeReservedCard(size_t i);

        const ResourceCard& takeReservedCard(const ResourceCard &card);

        void putResourceCard(const ResourceCard &card);

        void putNobleCard(const NobleCard &card);

        const ResourceCard** getReservedCards() { return ReservedCards; };
    };

    class PlayerExtStronghold : public Player{
    private:
        size_t availableStrongholds;

    public:
        size_t getAvailableStrongholds () {return availableStrongholds;}
        void putStrongholds();
        void takeStrongholds();
    };
}

#endif