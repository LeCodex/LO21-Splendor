#pragma once
#include "Splendor.h"

namespace Splendor
{
	class Bank
	{
	private:
		int tokens[6]{0, 0, 0, 0, 0, 0};

	public:
		Bank(int t[] = nullptr);

		bool empty(Token t) const { return tokens[t] == 0; }
		int amount(Token t) const { return tokens[t]; }
		const int *getAll() const { return tokens; }
		int take(Token t, int amount);
		int put(Token t, int amount);
	};
}
