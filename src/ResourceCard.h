#pragma once
#include "Player.h"
#include "BaseCard.h"
#include <sstream>

namespace Splendor
{
	class ResourceCard : public BaseCard
	{
	private:
		Token resource;
		int level;

	public:
		ResourceCard(int c[], int p, Token r, int l) : BaseCard(c, p), resource(r), level(l) {}

		Token getResource() const { return resource; }
		int getLevel() const { return level; }

		virtual std::string toString() const
		{
			std::stringstream s;
			s << BaseCard::toString();
			s << ", Resource : " << resource << ", ";
			s << "Level : " << level;
			return s.str();
		}
    };
}
