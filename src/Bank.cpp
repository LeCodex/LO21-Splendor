#include "Bank.h"

Splendor::Bank::Bank(int t[])
{
	if (t)
	{
		for (int i = 0; i < 6; i++)
			tokens[i] = t[i];
	}
}

int Splendor::Bank::take(Token t, int amount)
{
	int correctAmount = tokens[t] > amount ? amount : tokens[t];
	tokens[t] -= correctAmount;

	return correctAmount;
}

int Splendor::Bank::put(Token t, int amount)
{
    tokens[t] += amount;
    return tokens[t];
}
