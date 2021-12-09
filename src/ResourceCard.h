#pragma once
#include "basecard.h"

namespace Splendor {
	class ResourceCard : public BaseCard
	{
	private:
		Token resource;
		int level;
		// bool flipped; // Probably better to use hands as a mean of hiding the cards

	public:
		ResourceCard(int c[], int p, Token r, int l) : BaseCard(c, p), resource(r), level(l) {}

		Token getResource() const { return resource; }
		int getLevel() const { return level; }
		// bool getFlipped() const { return flipped; }
		// bool flip() { flipped = !flipped; return flipped; }
	};
}
