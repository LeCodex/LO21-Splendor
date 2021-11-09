#pragma once
#include "splendor.h";

namespace Splendor {
	class Card
	{
	private:
		int cost[5];
		int prestige;

		void setCost(int newCost[]) { for (size_t i = 0; i < 5; i++) cost[i] = newCost[i]; }
	public:
		Card(int c[], int p) : cost(), prestige(p) { setCost(c); }

		int* getFullCost() { return cost; }
		int getCost(size_t token) { return cost[token]; }
		int getPrestige() { return prestige; }
	};
}

