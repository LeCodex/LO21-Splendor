#pragma once
#include "Splendor.h"
#include <sstream>

namespace Splendor
{
	class BaseCard
	{
	private:
		int cost[5]{0, 0, 0, 0, 0}; // Will act as a map between Token and int (amount of that Token)
		int prestige;

		void setCost(int newCost[])
		{
			for (size_t i = 0; i < 5; i++)
				cost[i] = newCost[i];
		}

	public:
		BaseCard(int c[], int p) : cost(), prestige(p) { setCost(c); }

		const int *getFullCost() const { return cost; }
		int getCost(Token t) const { return cost[t]; }
		int getPrestige() const { return prestige; }

		virtual std::string toString() const
		{
			std::stringstream s;
			s << "Cost : [" << cost[0] << ", " << cost[1] << ", " << cost[2] << ", " << cost[3] << ", " << cost[4] << "],";
			s << "Prestige : " << prestige << "";
			return s.str();
		}

		void print(std::ostream &f = std::cout) const
		{
			f << toString() << "\n";
		}
	};
}
