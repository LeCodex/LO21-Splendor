#pragma once
#include "DrawPile.h"
// #include "player.h"

namespace Splendor
{
	class Hand : public DrawPile
	{
	private:
		// Player* owner; // Uncomment when Player is defined

	public:
		// Hand(Player* o): DrawPile(), owner(o) {}

		// Player& getOwner() const { return *owner; }
		// bool setOwner(Player& newOwner);
		const BaseCard &play(size_t index);
	};
}
