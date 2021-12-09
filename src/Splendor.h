#pragma once
#include <iostream>
#include <exception>

namespace Splendor
{
	enum Token
	{
		Red,
		Blue,
		Green,
		White,
		Black,
		Gold
	};

	class SplendorException : public std::exception
	{
	};
}