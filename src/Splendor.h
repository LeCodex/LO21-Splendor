#pragma once
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

	class SplendorException : public std::exception
	{
	};
}