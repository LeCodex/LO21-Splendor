#ifndef NOBLECARD_H
#define NOBLECARD_H

#include "BaseCard.h"

namespace Splendor
{
    class Player;

	class NobleCard : public BaseCard
	{
	public:
        NobleCard(int c[], int p) : BaseCard(c, p) {}
        virtual bool canBeTakenBy(Player& p) const;
	};

    class CitiesCard : public NobleCard
    {
    private:
        int otherCost = 0;
    public:
        CitiesCard(int c[], int p) : NobleCard(c, p) {
            otherCost = c[5];
        }
        bool canBeTakenBy(Player& p) const override;
        int getOtherCost() const { return otherCost; }
        void setOtherCost(int c) { otherCost = c; }
    };
}

#endif
