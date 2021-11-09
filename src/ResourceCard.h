#pragma once
#include "card.h";

namespace Splendor {
	class ResourceCard : public Card
	{
	private:
		int resource;

	public:
		ResourceCard(int c[], int p, int r): Card(c, p), resource(r) {}

		int getResource() { return resource; }
	};
}

