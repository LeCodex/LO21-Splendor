#pragma once
#include "basecard.h"

namespace Splendor {
	class ResourceCard : public BaseCard
	{
	private:
		Token resource;
		int level;

	public:
		ResourceCard(int c[], int p, Token r, int l): BaseCard(c, p), resource(r), level(l) {}

		Token getResource() const { return resource; }
		int getLevel() const { return level; }
	};
}
