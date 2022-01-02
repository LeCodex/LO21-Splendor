#ifndef SPLENDOR_H
#define SPLENDOR_H
#include <iostream>
#include <exception>

class View;

namespace Splendor
{
    class Game;

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

    template<typename T>
    class Singleton
    {
    protected:
        Singleton() noexcept = default;

        Singleton(const Singleton&) = delete;

        Singleton& operator=(const Singleton&) = delete;

        virtual ~Singleton() = default;

    public:
        static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
        {
            static T instance{};
            return instance;
        }
    };
}
#endif
