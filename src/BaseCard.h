#pragma once
#include "splendor.h";

namespace Splendor {
	class BaseCard
	{
	private:
		int cost[5]{ 0, 0, 0, 0, 0 }; // Will act as a map between Token and int
		int prestige;

		void setCost(int newCost[]) { for (size_t i = 0; i < 5; i++) cost[i] = newCost[i]; }
	public:
		BaseCard(int c[], int p) : cost(), prestige(p) { setCost(c); }

		int* getFullCost() { return cost; }
		int getCost(Token t) const { return cost[t]; }
		int getPrestige() const { return prestige; }
	};
}

