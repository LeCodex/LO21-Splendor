#pragma once
#include "splendor.h"

namespace Splendor {
	class Bank
	{
	private:
		int tokens[6]{ 0, 0, 0, 0, 0, 0 };

	public:
		Bank(int t[]) { for (int i = 0; i < 6; i++) tokens[i] = t[i]; }

		bool empty(Token t) const { return tokens[t] == 0; }
		int amount(Token t, int amount) const { return tokens[t]; }
		int take(Token t, int amount);
		int put(Token t, int amount);
	};
}

