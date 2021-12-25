#ifndef BOARD_H
#define BOARD_H

#include "ResourceCard.h"
#include "BaseCard.h"
#include "NobleCard.h"
#include "DrawPile.h"
#include "Bank.h"
#include <stdlib.h>
#include <vector>

using namespace std;
namespace Splendor
{
    class Board
    {
    private:
        const ResourceCard *cards[3][4];
        Bank bank;
        DrawPile drawpiles[3];
        vector<const NobleCard *> nobles;

    public:
        Board()
        {
            int t[6] = {7, 7, 7, 7, 7, 5};
            bank = Bank(t);
        }
        ~Board() = default;

        // Replinishers
        void fillDrawPile(size_t i, const ResourceCard &c);
        void fillNobles(const NobleCard &c);

        // Update functions
        void replenishCenterCards();

        // Takers
        const ResourceCard &takeCenterCard(size_t i, size_t j);
        // Surcharge pour la vue
        const ResourceCard &takeCenterCard(const ResourceCard &c);
        const ResourceCard &takeDrawCard(size_t i);
        const NobleCard &takeNobleCard(size_t i);
        // Surcharge pour la vue
        const NobleCard &takeNobleCard(const NobleCard &c);

        // Getters
        const ResourceCard &getCard(size_t i, size_t j)
        {
            if (i > 3 || j > 4)
                throw "Index out of bound\n";
            if (cards[i][j] == nullptr)
                throw "No cards here\n";
            return *cards[i][j];
        }
        Bank &getBank() { return bank; }
        DrawPile &getDrawPile(size_t i)
        {
            if (i > 3)
                throw "Index out of bound\n";
            return drawpiles[i];
        }
        vector<NobleCard const *> getNobles() { return nobles; }
    };
}
#endif