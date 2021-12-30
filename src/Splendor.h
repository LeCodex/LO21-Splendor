#ifndef SPLENDOR_H
#define SPLENDOR_H
#include <iostream>
#include <exception>

namespace Splendor
{
	enum Token
	{
		White,
		Blue,
		Green,
		Red,
		Black,
		Gold
	};

	inline std::string getTokenName(Token t)
	{
		switch (t)
		{
		case White:
			return "White";
		case Blue:
			return "Blue";
		case Green:
			return "Green";
		case Red:
			return "Red";
		case Black:
			return "Black";
		case Gold:
			return "Gold";
		}
		return "";
	}

	class SplendorException : public std::exception
	{
	};
}
#endif
